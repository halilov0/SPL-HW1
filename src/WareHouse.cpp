#pragma once
#include <fstream>
#include "WareHouse.h"
#include "Volunteer.h"
#include <iostream>
#include <sstream>
#include "Action.h"
using namespace std;

WareHouse::WareHouse(const string &configFilePath) : dv(new DriverVolunteer(NO_ORDER, "not real", -1, -1)), cv(new CollectorVolunteer(NO_ORDER, "not real", -1)), nullSCustomer(new SoldierCustomer(NO_CUSTOMER, "Not real", -1, -1)), nullCCustomer(new CivilianCustomer(NO_CUSTOMER, "Not real", -1, -1))
{
    string filePath = configFilePath; // replace with your own file path
    ifstream inputFile(filePath);
    customerCounter = 0;
    volunteerCounter = 0;
    ordersCounter = 0;
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
    isOpen = true;
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
            delete step;
        }
        else if (words[0] == "order")
        {
            int customerID = stoi(words[1]);
            Customer& customer = getCustomer(customerID);
            Order* order = new Order(ordersCounter, customerID, customer.getCustomerDistance());
            if (customer.addOrder(order->getId()) != -1) // returned orderId if added successfully
            {
                this->addOrder(order);
            }
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
            
            delete addCustomer;
        }
        else if (words[0] == "orderStatus")
        {
            PrintOrderStatus* orderStatus = new PrintOrderStatus(stoi(words[1]));
            orderStatus->act(*this);
            delete orderStatus;
        }
        else if (words[0] == "customerStatus")
        {
            PrintCustomerStatus* customerStatus = new PrintCustomerStatus(stoi(words[1]));
            customerStatus->act(*this);
            delete customerStatus;
        }
        else if (words[0] == "volunteerStatus")
        {
            PrintVolunteerStatus* volunteerStatus = new PrintVolunteerStatus(stoi(words[1]));
            volunteerStatus->act(*this);
            delete volunteerStatus;
        }
        else if (words[0] == "log")
        {
            PrintActionsLog* log = new PrintActionsLog();
            log->act(*this);
            delete log;
        }
        else if (words[0] == "close")
        {
            Close* close = new Close();
            close->act(*this);
            delete close;
        }
        else if (words[0] == "backup")
        {
            BackupWareHouse* backup = new BackupWareHouse();
            backup->act(*this);
            delete backup; 
        }
        else if (words[0] == "restore")
        {
            RestoreWareHouse* restore = new RestoreWareHouse();
            restore->act(*this);
            delete restore;
        }
        else
        {
            cout << "Invalid Command" << endl;
        }
    }
}

Volunteer &WareHouse::getNotBusyVolunteer(const Order &order, string flag)
{
    for(int i = 0; i < getVolunteers().size(); i++)
    {
        Volunteer* v = getVolunteers()[i];
        if(v->flag() == flag && v->canTakeOrder(order))
        {
            return *v;
        }
        
    }
    return *dv; //dv??
}

void WareHouse::removeUselessVolunteers()
{
    vector<Volunteer*> vec = getVolunteers();
    
    for(int i = 0; i < vec.size(); i++)
    {
        if(!(vec[i])->hasOrdersLeft())
        {
            delete vec[i];
            vec.erase(vec.begin() + i);
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
        cout << "Move order from complete list..." << endl;
    }
    // if (from == OrderType::PENDING)
    // {
    //     if (to == OrderType::INPROCESS)
    //     {
    //         inProcessOrders.push_back(order);
    //         removeOrder(order->getId(), pendingOrders);
    //     }
    //     else if(to == OrderType::COMPLETED)
    //     {
    //         //vector<Order*> newVec = getCompletedOrders();
    //         completedOrders.push_back(order);
    //         removeOrder(order->getId(), pendingOrders);
    //     }
    // }
    // else if(from == OrderType::INPROCESS)
    // {
    //     if(to == OrderType::COMPLETED)
    //     {
    //         vector<Order*> newVec = getCompletedOrders();
    //         newVec.push_back(order);
    //         removeOrder(order->getId(), inProcessOrders);
    //     }
    // }
    // else{
    //     cout << "not valid 'move order'" << endl;
    // }
}

void WareHouse::addOrder(Order* order)
{    
    AddOrder* addOrder = new AddOrder(order->getCustomerId());
    addOrder->act(*this);
    if (addOrder->getStatus() == ActionStatus::COMPLETED)
    {
        pendingOrders.push_back(order);
        ordersCounter++;
    }
    addAction(addOrder);
    delete addOrder;
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
    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i]->getId() == customerId)
            return *customers[i];
    }
    return *nullSCustomer;
    //throw std::runtime_error("Customer not found");
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (int i = 0; i < volunteers.size(); i++)
    {
        if (volunteers[i]->getId() == volunteerId)
            return *volunteers[i];
    }
    
    throw std::runtime_error("Volunteer not found");
}

Order &WareHouse::getOrder(int orderId) const
{
    for (int i = 0; i < pendingOrders.size(); i++)
    {
        if (pendingOrders[i]->getId() == orderId)
            return *pendingOrders[i];
    }
    for (int i = 0; i < inProcessOrders.size(); i++)
    {
        if (inProcessOrders[i]->getId() == orderId)
            return *inProcessOrders[i];
    }
    for (int i = 0; i < completedOrders.size(); i++)
    {
        if (completedOrders[i]->getId() == orderId)
            return *completedOrders[i];
    }    
    throw std::runtime_error("Order not found");
}

const vector<BaseAction*> &WareHouse::getActions() const
{    
    return actionsLog;
}

void close()
{

}
void open()
{

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



void WareHouse::addVolunteer(Volunteer* volunteer)
{
    volunteers.push_back(volunteer);
    volunteerCounter++;
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


void WareHouse::removeOrder(int id, vector<Order*>& ordersToRemove)
{
    // vector<Order*> vec;
    // if(from == OrderType::PENDING)
    // {
    //     vec = getPendingOrders();
    // }
    // else if(from == OrderType::INPROCESS)
    // {
    //     vec = getInProcessOrders();
    // }
    // else
    // {
    //     vec = getCompletedOrders();
    // }
    
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
WareHouse::WareHouse(const WareHouse& other) : isOpen(other.isOpen), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter),  ordersCounter(other.ordersCounter)                                                                                        
{
    dv = other.dv->clone();
    cv = other.cv->clone();
    nullSCustomer = other.nullSCustomer->clone();
    nullCCustomer = other.nullCCustomer->clone();

    for (int i = 0; i < other.actionsLog.size(); i++)
        actionsLog.push_back(other.actionsLog.at(i) -> clone());
    for (int i = 0; i < other.volunteers.size(); i++)
        volunteers.push_back(other.volunteers.at(i) -> clone());
    for (int i = 0; i < other.pendingOrders.size(); i++)
        pendingOrders.push_back(other.pendingOrders.at(i) -> clone());
    for (int i = 0; i < other.inProcessOrders.size(); i++)
        inProcessOrders.push_back(other.inProcessOrders.at(i) -> clone());
    for (int i = 0; i < other.completedOrders.size(); i++)
        completedOrders.push_back(other.completedOrders.at(i) -> clone());
    for (int i = 0; i < other.customers.size(); i++)
        customers.push_back(other.customers.at(i) -> clone());
}

// destructor
WareHouse::~WareHouse()
{
    delete dv;
    delete cv;
    delete nullSCustomer;
    delete nullCCustomer;

    for (int i = 0; i < actionsLog.size(); i++)
        delete actionsLog.at(i);
    for (int i = 0; i < volunteers.size(); i++)
        delete volunteers.at(i);
    for (int i = 0; i < pendingOrders.size(); i++)
        delete pendingOrders.at(i);
    for (int i = 0; i < inProcessOrders.size(); i++)
        delete inProcessOrders.at(i);
    for (int i = 0; i < completedOrders.size(); i++)
        delete completedOrders.at(i);
    for (int i = 0; i < customers.size(); i++)
        delete customers.at(i);
}

// assignment operator
void WareHouse::operator=(const WareHouse& other)
{
    if(this != &other)
    {
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        ordersCounter = other.ordersCounter;

        delete dv;
        dv = other.dv->clone();
        delete cv;
        cv = other.cv->clone();
        delete nullSCustomer;
        nullSCustomer = other.nullSCustomer->clone();
        delete nullCCustomer;
        nullCCustomer = other.nullCCustomer->clone(); 

        for (int i = 0; i < actionsLog.size(); i++)
            delete actionsLog.at(i);
        actionsLog.clear();
        for (int i = 0; i < other.actionsLog.size(); i++)
            actionsLog.push_back(other.actionsLog.at(i) -> clone());


        for (int i = 0; i < volunteers.size(); i++)
            delete volunteers.at(i);
        volunteers.clear();
        for (int i = 0; i < other.volunteers.size(); i++)
            volunteers.push_back(other.volunteers.at(i) -> clone());
        
        
        for (int i = 0; i < pendingOrders.size(); i++)
            delete pendingOrders.at(i);
        pendingOrders.clear();
        for (int i = 0; i < other.pendingOrders.size(); i++)
            pendingOrders.push_back(other.pendingOrders.at(i) -> clone());
        
        
        for (int i = 0; i < inProcessOrders.size(); i++)
            delete inProcessOrders.at(i);
        inProcessOrders.clear();
        for (int i = 0; i < other.inProcessOrders.size(); i++)
            inProcessOrders.push_back(other.inProcessOrders.at(i) -> clone());
        
        
        for (int i = 0; i < completedOrders.size(); i++)
            delete completedOrders.at(i);
        completedOrders.clear();
        for (int i = 0; i < other.completedOrders.size(); i++)
            completedOrders.push_back(other.completedOrders.at(i) -> clone());
        
        
        for (int i = 0; i < customers.size(); i++)
            delete customers.at(i);   
        customers.clear();
        for (int i = 0; i < other.customers.size(); i++)
            customers.push_back(other.customers.at(i) -> clone());
    }
}

// move constructor 
WareHouse::WareHouse(WareHouse&& other) noexcept : isOpen(other.isOpen), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter),  ordersCounter(other.ordersCounter)
{
    dv = other.dv;
    other.dv = nullptr;
    cv = other.cv;
    other.cv = nullptr;
    nullSCustomer = other.nullSCustomer;
    other.nullSCustomer = nullptr;
    nullCCustomer = other.nullCCustomer;
    other.nullCCustomer = nullptr;   
}

void WareHouse::operator=(WareHouse&& other) noexcept
{
    if(this != &other)
    {
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        ordersCounter = other.ordersCounter;

        delete dv;
        dv = other.dv;
        delete cv;
        cv = other.cv;
        delete nullSCustomer;
        nullSCustomer = other.nullSCustomer;
        delete nullCCustomer;
        nullCCustomer = other.nullCCustomer; 


        for (int i = 0; i < actionsLog.size(); i++)
            delete actionsLog.at(i);
        actionsLog.clear();
        for (int i = 0; i < other.actionsLog.size(); i++)
            actionsLog.push_back(other.actionsLog.at(i));


        for (int i = 0; i < volunteers.size(); i++)
            delete volunteers.at(i);
        volunteers.clear();
        for (int i = 0; i < other.volunteers.size(); i++)
            volunteers.push_back(other.volunteers.at(i));
        
        
        for (int i = 0; i < pendingOrders.size(); i++)
            delete pendingOrders.at(i);
        pendingOrders.clear();
        for (int i = 0; i < other.pendingOrders.size(); i++)
            pendingOrders.push_back(other.pendingOrders.at(i));
        
        
        for (int i = 0; i < inProcessOrders.size(); i++)
            delete inProcessOrders.at(i);
        inProcessOrders.clear();
        for (int i = 0; i < other.inProcessOrders.size(); i++)
            inProcessOrders.push_back(other.inProcessOrders.at(i));
        
        
        for (int i = 0; i < completedOrders.size(); i++)
            delete completedOrders.at(i);
        completedOrders.clear();
        for (int i = 0; i < other.completedOrders.size(); i++)
            completedOrders.push_back(other.completedOrders.at(i));
        
        
        for (int i = 0; i < customers.size(); i++)
            delete customers.at(i);   
        customers.clear();
        for (int i = 0; i < other.customers.size(); i++)
            customers.push_back(other.customers.at(i));
    }
}









