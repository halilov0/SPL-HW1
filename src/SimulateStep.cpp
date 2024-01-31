#pragma once
#include "Action.h"
#include "Volunteer.h"
#include <iostream>
#include "WareHouse.h"
using namespace std;

SimulateStep::SimulateStep(int NumOfSteps) : numOfSteps(NumOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse)
{
    for (int i = 0; i < wareHouse.getPendingOrders().size(); i++)
    {
        Order* o = wareHouse.getPendingOrders()[i];
        // checks if order is waiting to be collected
        if(o->getStatus() == OrderStatus::PENDING)
        {
           // checking if there is free collector
           Volunteer& Collector =  wareHouse.getNotBusyCollector(*o);
           // assume id = no_order is fake volunteer
           if(Collector.getId() != NO_ORDER)
           {
                Collector.acceptOrder(*o);
                //Collector.step();
                o->setCollectorId(Collector.getId());
                o->setStatus(OrderStatus::COLLECTING);
                wareHouse.moveOrder(o, OrderType::PENDING, OrderType::INPROCESS);
           }
        }            
        
        // checks if order is waiting to be delivered
        if(o->getStatus() == OrderStatus::COLLECTING)     
        {
            // checking if there is free driver
            Volunteer& Driver =  wareHouse.getNotBusyDriver(*o);
           // assume id = no_order is fake volunteer
            if(Driver.getId() != NO_ORDER)
            {
                Driver.acceptOrder(*o);
              //  Driver.step();
                o->setDriverId(Driver.getId());
                o->setStatus(OrderStatus::DELIVERING);
                wareHouse.moveOrder(o, OrderType::PENDING, OrderType::INPROCESS);
            }
        }  
    } 

    for (int i = 0; i < wareHouse.getInProcessOrders().size(); i++)
    {
        Order* o = wareHouse.getInProcessOrders()[i];
        int id;
        if(o->getCollectorId() == NO_VOLUNTEER)
            id = o->getDriverId();
        else if (o->getDriverId() == NO_VOLUNTEER)
        {
            id = o->getCollectorId();
        }
        Volunteer& v = wareHouse.getVolunteer(id);
        v.step();
        // volunteer finished
        if(!v.isBusy())
        {
            // push the order to the right list
            if(o->getStatus() == OrderStatus::COLLECTING)
            {
                wareHouse.moveOrder(o, OrderType::INPROCESS, OrderType::PENDING);
                o->setCollectorId(NO_VOLUNTEER);
            }
            else if (o->getStatus() == OrderStatus::DELIVERING)
            {
                wareHouse.moveOrder(o, OrderType::INPROCESS, OrderType::COMPLETED);
                o->setDriverId(NO_VOLUNTEER);
            }           
        }
    }
    wareHouse.removeUselessVolunteers();   
}

string SimulateStep::toString() const
{

}

SimulateStep* SimulateStep::clone() const
{
    return new SimulateStep(*this);
}



