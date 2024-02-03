#include <fstream>
#include "WareHouse.h"
#include "Volunteer.h"
#include <iostream>
#include <sstream>
#include "Action.h"
using namespace std;

WareHouse::WareHouse(const string &configFilePath) : 
isOpen(false), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(), customerCounter(0), volunteerCounter(0), ordersCounter(0),
nullV(new DriverVolunteer(NULL_OBJECT, "not real", NULL_OBJECT, NULL_OBJECT)), nullC(new SoldierCustomer(NULL_OBJECT, "Not real", NULL_OBJECT, NULL_OBJECT)), nullO(new Order(NULL_OBJECT, NULL_OBJECT, NULL_OBJECT))
{
    string filePath = configFilePath; // replace with your own file path
    ifstream inputFile(filePath);

    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line, '\n'))
        {
            string word;
            stringstream lines(line);
            vector<string> v;
            while (getline(lines, word, ' ')) 
                v.push_back(word);
            
            if (v.size() > 0)
            {
                if (v[0] == "customer")
                {
                    if(v[2] == "soldier")
                    {     
                        Customer *temp = new SoldierCustomer(customerCounter, v[1], stoi(v[3]), stoi(v[4]));              
                        addCustomer(temp);
                    }
                    else if(v[2] == "civilian")
                    {
                        Customer *temp = new CivilianCustomer(customerCounter, v[1], stoi(v[3]), stoi(v[4]));              
                        addCustomer(temp);
                    }
                }            
                else if (v[0] == "volunteer")
                {
                    if (v[2] == "collector")
                    {
                        CollectorVolunteer* temp = new CollectorVolunteer(volunteerCounter, v[1], stoi(v[3]));
                        addVolunteer(temp);
                    }
                    else if (v[2] == "limited_collector")
                    {
                        LimitedCollectorVolunteer* temp = new LimitedCollectorVolunteer(volunteerCounter, v[1], stoi(v[3]), stoi(v[4]));
                        addVolunteer(temp);
                    }
                    else if (v[2] == "driver")
                    {
                        DriverVolunteer* temp = new DriverVolunteer(volunteerCounter, v[1], stoi(v[3]), stoi(v[4]));
                        addVolunteer(temp);
                    }
                    else if (v[2] == "limited_driver")
                    {
                        LimitedDriverVolunteer* temp = new LimitedDriverVolunteer(volunteerCounter, v[1], stoi(v[3]), stoi(v[4]), stoi(v[5]));
                        addVolunteer(temp);
                    }
                }
            }
        }
        inputFile.close();
    }   
}

void WareHouse::start()
{
    open();
    cout << "Warehouse is open!" << endl; 
    while (isOpen)
    {
        string input;
        getline(std::cin, input);
        stringstream iss(input);
        vector<std::string> words;
        string word;
        while (iss >> word) {
            words.push_back(word);
        }

        if (words[0] == "step")
        {
            SimulateStep* step = new SimulateStep(stoi(words[1]));
            step->act(*this);
        }
        else if (words[0] == "order")
        {
            int customerID = stoi(words[1]);
            Customer& customer = getCustomer(customerID);
            Order* order = new Order(ordersCounter, customerID, customer.getCustomerDistance());
            this->addOrder(order);
        }
        else if (words[0] == "customer")
        {
            Customer *temp;
            
            string name = words[1];
            string customerType = words[2];
            int locationDistance = stoi(words[3]);
            int maxOrders = stoi(words[4]);

            if (customerType == "soldier")     
                temp = new SoldierCustomer(customerCounter, name, locationDistance, maxOrders);
            else if (customerType == "civilian")
                temp = new CivilianCustomer(customerCounter, name, locationDistance, maxOrders);
            else
                cout << "no such customer type" << endl;
            
            AddCustomer* addCustomer = new AddCustomer(name, customerType, locationDistance, maxOrders);
            addCustomer->act(*this);
            
            if (addCustomer->getStatus() == ActionStatus::COMPLETED) //Should not result error
                this->addCustomer(temp);
        }
        else if (words[0] == "orderStatus")
        {
            PrintOrderStatus* orderStatus = new PrintOrderStatus(stoi(words[1]));
            orderStatus->act(*this);
        }
        else if (words[0] == "customerStatus")
        {
            PrintCustomerStatus* customerStatus = new PrintCustomerStatus(stoi(words[1]));
            customerStatus->act(*this);
        }
        else if (words[0] == "volunteerStatus")
        {
            PrintVolunteerStatus* volunteerStatus = new PrintVolunteerStatus(stoi(words[1]));
            volunteerStatus->act(*this);
        }
        else if (words[0] == "log")
        {
            PrintActionsLog* log = new PrintActionsLog();
            log->act(*this);
        }
        else if (words[0] == "close")
        {
            Close* close = new Close();
            close->act(*this);
        }
        else if (words[0] == "backup")
        {
            BackupWareHouse* backup = new BackupWareHouse();
            backup->act(*this);
        }
        else if (words[0] == "restore")
        {
            RestoreWareHouse* restore = new RestoreWareHouse();
            restore->act(*this);
        }
        else
        {
            cout << "Invalid Command" << endl;
        }
    }
}

Volunteer &WareHouse::getNotBusyVolunteer(const Order &order, string flag)
{
    for(int i = 0; i < (int)getVolunteers().size(); i++)
    {
        Volunteer* v = volunteers[i];
        if(v->flag() == flag && v->canTakeOrder(order))
            return *v;
    }
    return *nullV; 
}

void WareHouse::removeUselessVolunteers()
{    
    for(int i = 0; i < (int)volunteers.size(); i++)
    {
        if(!volunteers[i]->hasOrdersLeft() && !volunteers[i]->isBusy())
        {
            delete volunteers[i];
            volunteers.erase(volunteers.begin() + i);
        }    
    }
}

void WareHouse::moveOrder(Order* order, OrderType from, OrderType to)
{
    if (from == OrderType::PENDING)
    {
        inProcessOrders.push_back(order);
        removeOrder(order->getId(), pendingOrders);
    }
    else if (from == OrderType::INPROCESS)
    {
        if (to == OrderType::PENDING)
        {
            pendingOrders.push_back(order);
            removeOrder(order->getId(), inProcessOrders);
        }
        else
        {
            completedOrders.push_back(order);
            removeOrder(order->getId(), inProcessOrders);
        }
    }
    else
    {
        cout << "Cannot move order from complete list" << endl;
    }
}

void WareHouse::addOrder(Order* order)
{    
    AddOrder* addOrder = new AddOrder(order->getCustomerId());
    addOrder->act(*this);
    if (addOrder->getStatus() == ActionStatus::COMPLETED)
    {
        Customer& c = getCustomer(order->getCustomerId()); 
        c.addOrder(order->getId());
        pendingOrders.push_back(order);
        ordersCounter++;
    }
    else
        delete order;
}

void WareHouse::addCustomer(Customer* customer)
{   
    customers.push_back(customer);
    customerCounter++;
}

void WareHouse::addAction(BaseAction* action)
{
    actionsLog.push_back(action);
}

Customer &WareHouse::getCustomer(int customerId) const
{
    for (int i = 0; i < (int)customers.size(); i++)
    {
        if (customers[i]->getId() == customerId)
            return *customers[i];
    }
    return *nullC;
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (int i = 0; i < (int)volunteers.size(); i++)
    {
        if (volunteers[i]->getId() == volunteerId)
            return *volunteers[i];
    }
    
    return *nullV;
}

Order &WareHouse::getOrder(int orderId) const
{
    for (int i = 0; i < (int)pendingOrders.size(); i++)
    {
        if (pendingOrders[i]->getId() == orderId)
            return *pendingOrders[i];
    }
    for (int i = 0; i < (int)inProcessOrders.size(); i++)
    {
        if (inProcessOrders[i]->getId() == orderId)
            return *inProcessOrders[i];
    }
    for (int i = 0; i < (int)completedOrders.size(); i++)
    {
        if (completedOrders[i]->getId() == orderId)
            return *completedOrders[i];
    }    
    return *nullO;
}

void WareHouse::addVolunteer(Volunteer* volunteer)
{
    volunteers.push_back(volunteer);
    volunteerCounter++;
}

void WareHouse::removeOrder(int id, vector<Order*>& ordersToRemove)
{  
    for(vector<Order*>::iterator itr = ordersToRemove.begin(); ordersToRemove.size() > 0 && itr != ordersToRemove.end(); )
    {
        if((*itr)->getId() == id)
        {
            ordersToRemove.erase(itr);
        }
        else 
            itr++;    
    }
}

// rule of 5

//copy constructor
WareHouse::WareHouse(const WareHouse& other) : isOpen(other.isOpen), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(),
customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter),  ordersCounter(other.ordersCounter),
nullV(other.nullV->clone()), nullC(other.nullC->clone()), nullO(other.nullO->clone())                                                                                        
{
    for (int i = 0; i < (int)other.actionsLog.size(); i++)
        actionsLog.push_back(other.actionsLog.at(i) -> clone());
    for (int i = 0; i < (int)other.volunteers.size(); i++)
        volunteers.push_back(other.volunteers.at(i) -> clone());
    for (int i = 0; i < (int)other.pendingOrders.size(); i++)
        pendingOrders.push_back(other.pendingOrders.at(i) -> clone());
    for (int i = 0; i < (int)other.inProcessOrders.size(); i++)
        inProcessOrders.push_back(other.inProcessOrders.at(i) -> clone());
    for (int i = 0; i < (int)other.completedOrders.size(); i++)
        completedOrders.push_back(other.completedOrders.at(i) -> clone());
    for (int i = 0; i < (int)other.customers.size(); i++)
        customers.push_back(other.customers.at(i) -> clone());
}

// destructor
WareHouse::~WareHouse()
{
    delete nullV;
    delete nullC;
    delete nullO;

    for (int i = 0; i < (int)actionsLog.size(); i++)
        delete actionsLog[i];
    for (int i = 0; i < (int)volunteers.size(); i++)
        delete volunteers[i];
    for (int i = 0; i < (int)pendingOrders.size(); i++)
        delete pendingOrders[i];
    for (int i = 0; i < (int)inProcessOrders.size(); i++)
        delete inProcessOrders[i];
    for (int i = 0; i < (int)completedOrders.size(); i++)
        delete completedOrders[i];
    for (int i = 0; i < (int)customers.size(); i++)
        delete customers[i];
}

// assignment operator
WareHouse& WareHouse::operator=(const WareHouse& other)
{
    if(this != &other)
    {
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        ordersCounter = other.ordersCounter;

        delete nullV;
        nullV = other.nullV->clone();
        delete nullC;
        nullC = other.nullC->clone();
        delete nullO;
        nullO = other.nullO->clone(); 

        for (int i = 0; i < (int)actionsLog.size(); i++)
            delete actionsLog.at(i);
        actionsLog.clear();
        for (int i = 0; i < (int)other.actionsLog.size(); i++)
            actionsLog.push_back(other.actionsLog.at(i) -> clone());


        for (int i = 0; i < (int)volunteers.size(); i++)
            delete volunteers.at(i);
        volunteers.clear();
        for (int i = 0; i < (int)other.volunteers.size(); i++)
            volunteers.push_back(other.volunteers.at(i) -> clone());
        
        
        for (int i = 0; i < (int)pendingOrders.size(); i++)
            delete pendingOrders.at(i);
        pendingOrders.clear();
        for (int i = 0; i < (int)other.pendingOrders.size(); i++)
            pendingOrders.push_back(other.pendingOrders.at(i) -> clone());
        
        
        for (int i = 0; i < (int)inProcessOrders.size(); i++)
            delete inProcessOrders.at(i);
        inProcessOrders.clear();
        for (int i = 0; i < (int)other.inProcessOrders.size(); i++)
            inProcessOrders.push_back(other.inProcessOrders.at(i) -> clone());
        
        
        for (int i = 0; i < (int)completedOrders.size(); i++)
            delete completedOrders.at(i);
        completedOrders.clear();
        for (int i = 0; i < (int)other.completedOrders.size(); i++)
            completedOrders.push_back(other.completedOrders.at(i) -> clone());
        
        
        for (int i = 0; i < (int)customers.size(); i++)
            delete customers.at(i);   
        customers.clear();
        for (int i = 0; i < (int)other.customers.size(); i++)
            customers.push_back(other.customers.at(i) -> clone());
    }
    return *this;
}

// move constructor 
WareHouse::WareHouse(WareHouse&& other) noexcept : 
isOpen(other.isOpen), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(),
customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter),  ordersCounter(other.ordersCounter),
nullV(other.nullV), nullC(other.nullC), nullO(other.nullO)                                                                                        
{
    other.nullV = nullptr;
    other.nullC = nullptr;
    other.nullO = nullptr;
}

WareHouse& WareHouse::operator=(WareHouse&& other) noexcept
{
    if(this != &other)
    {
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        ordersCounter = other.ordersCounter;

        delete nullV;
        nullV = other.nullV;
        delete nullC;
        nullC = other.nullC;
        delete nullO;
        nullO = other.nullO; 


        for (int i = 0; i < (int)actionsLog.size(); i++)
            delete actionsLog.at(i);
        actionsLog.clear();
        for (int i = 0; i < (int)other.actionsLog.size(); i++)
            actionsLog.push_back(other.actionsLog.at(i));


        for (int i = 0; i < (int)volunteers.size(); i++)
            delete volunteers.at(i);
        volunteers.clear();
        for (int i = 0; i < (int)other.volunteers.size(); i++)
            volunteers.push_back(other.volunteers.at(i));
        
        
        for (int i = 0; i < (int)pendingOrders.size(); i++)
            delete pendingOrders.at(i);
        pendingOrders.clear();
        for (int i = 0; i < (int)other.pendingOrders.size(); i++)
            pendingOrders.push_back(other.pendingOrders.at(i));
        
        
        for (int i = 0; i < (int)inProcessOrders.size(); i++)
            delete inProcessOrders.at(i);
        inProcessOrders.clear();
        for (int i = 0; i < (int)other.inProcessOrders.size(); i++)
            inProcessOrders.push_back(other.inProcessOrders.at(i));
        
        
        for (int i = 0; i < (int)completedOrders.size(); i++)
            delete completedOrders.at(i);
        completedOrders.clear();
        for (int i = 0; i < (int)other.completedOrders.size(); i++)
            completedOrders.push_back(other.completedOrders.at(i));
        
        
        for (int i = 0; i < (int)customers.size(); i++)
            delete customers.at(i);   
        customers.clear();
        for (int i = 0; i < (int)other.customers.size(); i++)
            customers.push_back(other.customers.at(i));
    }
    return *this;
}


void WareHouse::close()
{
    isOpen = false; 
}

void WareHouse::open()
{
    isOpen = true;
}

const vector<BaseAction*> &WareHouse::getActions() const
{    
    return actionsLog;
}
const vector<Volunteer*>& WareHouse::getVolunteers()
{
    return volunteers;
}
const vector<Customer*>& WareHouse::getCustomers()
{
    return customers;
}
const vector<Order*>& WareHouse::getPendingOrders()
{
    return pendingOrders;
}
const vector<Order*>& WareHouse::getInProcessOrders()
{
    return inProcessOrders;
}
const vector<Order*>& WareHouse::getCompletedOrders()
{
    return completedOrders;
}
int WareHouse::getOrdersCounter() const
{
    return ordersCounter;
}
int WareHouse::getCustomerCounter() const
{
    return customerCounter;
}
int WareHouse::getVolunteerCounter() const
{
    return volunteerCounter;
}