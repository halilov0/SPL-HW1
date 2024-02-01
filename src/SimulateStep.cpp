#pragma once
#include "Action.h"
#include "Volunteer.h"
#include <iostream>
#include "WareHouse.h"
using namespace std;

SimulateStep::SimulateStep(int NumOfSteps) : numOfSteps(NumOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse)
{
    //Iterate through all pending-orders
    bool moved = false;
    int currentOrder = 0;
    while (currentOrder < wareHouse.getPendingOrders().size())
    {
        Order* order = wareHouse.getPendingOrders()[currentOrder];
        if (order->getStatus() == OrderStatus::PENDING)
        {
            Volunteer& collector = wareHouse.getNotBusyVolunteer(*order, "c"); //flag "c"
            if (collector.getId() != NO_ORDER) // if it isn't the "fake" volunteer
            {
                collector.acceptOrder(*order);
                order->setCollectorId(collector.getId());
                order->setStatus(OrderStatus::COLLECTING);
                
                wareHouse.moveOrder(order, OrderType::PENDING, OrderType::INPROCESS);
                moved = true;
            }
        }
        else if (order->getStatus() == OrderStatus::COLLECTING)
        {
            Volunteer& driver = wareHouse.getNotBusyVolunteer(*order, "d"); //flag "c"
            if (driver.getId() != NO_ORDER) // if it isn't the "fake" volunteer
            {
                driver.acceptOrder(*order);
                order->setDriverId(driver.getId());
                order->setStatus(OrderStatus::DELIVERING);
                
                wareHouse.moveOrder(order, OrderType::PENDING, OrderType::INPROCESS);
                moved = true;
            }
        }
        else
            moved = false;

        if (!moved)
            currentOrder++;
    }

    moved = false;
    currentOrder = 0;
    while (currentOrder < wareHouse.getInProcessOrders().size())
    {
        Order* order = wareHouse.getInProcessOrders()[currentOrder];
        int volunteerID;
        
        if (order->getStatus() == OrderStatus::COLLECTING)
            volunteerID = order->getCollectorId();
        else
            volunteerID = order->getDriverId();
        
        Volunteer& volunteer = wareHouse.getVolunteer(volunteerID);
        volunteer.step();

        // Checks if volunteer finished
        if (!volunteer.isBusy())
        {
            // Pushes the order to the correct list
            if(order->getStatus() == OrderStatus::COLLECTING)
            {
                // Done with collector and go to pendings in order to wait to for a driver 
                wareHouse.moveOrder(order, OrderType::INPROCESS, OrderType::PENDING);
                moved = true;
            }
            else if (order->getStatus() == OrderStatus::DELIVERING)
            {
                // Done with driver and go to complete 
                wareHouse.moveOrder(order, OrderType::INPROCESS, OrderType::COMPLETED);
                order->setStatus(OrderStatus::COMPLETED);
                moved = true;
            }  
        }
        else
            moved = false;

        if (!moved)
            currentOrder++;
    }
    wareHouse.removeUselessVolunteers();   
    wareHouse.addAction(this);
}

string SimulateStep::toString() const
{
    return "simulateStep " + std::to_string(numOfSteps) + " " + getActionStatusString();
}

SimulateStep* SimulateStep::clone() const
{
    return new SimulateStep(*this);
}



