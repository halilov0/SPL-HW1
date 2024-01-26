#pragma once
#include <fstream>
#include "WareHouse.h"
#include "/home/users/bsc/halilovi/Projects/SPL HW1/include/Volunteer.h"
#include <iostream>
#include <sstream>
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