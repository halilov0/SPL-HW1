#pragma once
#include <fstream>
#include "WareHouse.h"
#include "Volunteer.h"
#include <iostream>
#include <sstream>
#include "Action.h"
using namespace std;

WareHouse::WareHouse(const string &configFilePath) : dv(new DriverVolunteer(NO_ORDER, "not real", -1, -1)), cv(new CollectorVolunteer(NO_ORDER, "not real", -1)) 
{
    string filePath = configFilePath; // replace with your own file path
    ifstream inputFile(filePath);
    customerCounter = 0;
    volunteerCounter = 0;
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

            if(v[0] == "customer")
            {
                if(v[2] == "soldier")
                {     
                    Customer *temp = new SoldierCustomer(customerCounter, v[1], stoi(v[3]), stoi(v[4]));              
                    customers.push_back(temp);
                    customerCounter = customerCounter + 1;
                }
                else if(v[2] == "civilian")
                {
                    Customer *temp = new CivilianCustomer(customerCounter, v[1], stoi(v[3]), stoi(v[4]));              
                    customers.push_back(temp);
                    customerCounter = customerCounter + 1;
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
            AddOrder* order = new AddOrder(stoi(words[1]));
            order->act(*this);
            ordersCounter++;
            delete order;
        }
        else if (words[0] == "customer")
        {
            AddCustomer* customer = new AddCustomer(words[1], words[2], stoi(words[3]), stoi(words[4]));
            customer->act(*this);
            customerCounter++;
            delete customer;
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
            cout << "Invalid Command";
        }
    }
}

Volunteer &WareHouse::getNotBusyDriver(const Order &order)
{
    for(int i = 0; i<getVolunteers().size(); i++)
    {
        Volunteer* v = getVolunteers()[i];
        if(v->flag() == "d" && v->canTakeOrder(order))
        {
            return *v;
        }
        
    }
    return *dv;
}

Volunteer &WareHouse::getNotBusyCollector(const Order &order)
{
    for(int i = 0; i<getVolunteers().size(); i++)
    {
        Volunteer* v = getVolunteers()[i];
        if(v->flag() == "c" && v->canTakeOrder(order))
        {
            return *v;
        }
        
    }
    return *dv;
}

void WareHouse::removeUselessVolunteers()
{
    vector<Volunteer*> vec = getVolunteers();
    
    for(vector<Volunteer*>::iterator itr = vec.begin(); itr != vec.end(); itr++)
    {
        if(!(*itr)->hasOrdersLeft())
        {
            vec.erase(itr);
            delete *itr;
        }    
    }
}

void WareHouse::moveOrder(Order* order, OrderType from, OrderType to)
{
    Order* o = order;
    if(from == OrderType::PENDING)
    {
        if(to == OrderType::INPROCESS)
        {
            vector<Order*> newVec = getInProcessOrders();
            newVec.push_back(o);
            removeOrder(o->getId(), OrderType::PENDING);
        }
        else if(to == OrderType::COMPLETED)
        {
            vector<Order*> newVec = getCompletedOrders();
            newVec.push_back(o);
            removeOrder(o->getId(), OrderType::PENDING);
        }
    }
    else if(from == OrderType::INPROCESS)
    {
        if(to == OrderType::COMPLETED)
        {
            vector<Order*> newVec = getCompletedOrders();
            newVec.push_back(o);
            removeOrder(o->getId(), OrderType::INPROCESS);
        }
    }
    else{
        cout << "not valid 'move order'" << endl;
    }
}

void WareHouse::removeOrder(int id, OrderType from)
{
    vector<Order*> vec;
    if(from == OrderType::PENDING)
    {
        vec = getPendingOrders();
    }
    else if(from == OrderType::INPROCESS)
    {
        vec = getInProcessOrders();
    }
    else
    {
        vec = getCompletedOrders();
    }
    
    for(vector<Order*>::iterator itr = vec.begin(); itr != vec.end(); itr++)
    {
        if((*itr)->getId() == id)
        {
            vec.erase(itr);
        }    
    }
}