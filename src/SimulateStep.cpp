#pragma once
#include "/home/users/bsc/halilovi/Projects/SPL HW1/include/Action.h"
#include "/home/users/bsc/halilovi/Projects/SPL HW1/include/Volunteer.h"
#include <iostream>
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
           if(Collector.getId() != NO_ORDER)
           {
                Collector.acceptOrder(*o);
                Collector.step();
                o->setCollectorId(Collector.getId());
           }
        }
        
        // checks if order is waiting to be delivered
        if(o->getStatus() == OrderStatus::COLLECTING)     
        {
            // checking if there is free driver
            Volunteer& Driver =  wareHouse.getNotBusyDriver(*o);
            if(Driver.getId() != NO_ORDER)
            {
                Driver.acceptOrder(*o);
                Driver.step();
                o->setDriverId(Driver.getId());
            }
        }   
           
            
        //         wareHouse.getVolunteer(id).step();
                
        //         {
        //             o->setCollectorId(NO_ORDER);
        //         }
        //     }
        //     // order waiting to be delivered
        //     else
        //     {
        //         // if there is free driver
        //         Volunteer& v = wareHouse.getNotBusyDriver(*o);
        //         if(v.getId() != NO_ORDER)
        //         {
        //             v.acceptOrder(*o);
        //             o->setStatus(OrderStatus::DELIVERING);
        //         }
        //     }
        // }


        // if(o->getStatus() == OrderStatus::DELIVERING)
        // {
        //     int id = o->getDriverId();
        //     wareHouse.getVolunteer(id).step();
        // }
    }























    // for (int i = 0; i < wareHouse.getInProcessOrders().size(); i++)
    // {
    //     Order* o = wareHouse.getInProcessOrders()[i];
    //     // checks if order is being collected
    //     if(o->getStatus() == OrderStatus::COLLECTING)
    //     {
    //         int id = o->getCollectorId();
    //         if(id != NO_ORDER)
    //         // order is being collected
    //         {
    //             wareHouse.getVolunteer(id).step();
    //             if(wareHouse.getVolunteer(id).canTakeOrder(*o))
    //             {
    //                 o->setCollectorId(NO_ORDER);
    //             }
    //         }
    //         // order waiting to be delivered
    //         else
    //         {
    //             // if there is free driver
    //             Volunteer& v = wareHouse.getNotBusyDriver(*o);
    //             if(v.getId() != NO_ORDER)
    //             {
    //                 v.acceptOrder(*o);
    //                 o->setStatus(OrderStatus::DELIVERING);
    //             }
    //         }
    //     }


    //     if(o->getStatus() == OrderStatus::DELIVERING)
    //     {
    //         int id = o->getDriverId();
    //         wareHouse.getVolunteer(id).step();
    //     }
    // }



    // for (int i = 0; i < wareHouse.getPendingOrders().size(); i++)
    // {        
    //     //We will not use getOrder(ID) because the ID regards to ordersCounter which can refer to an order that is not on pending-order list
    //     if (wareHouse.getPendingOrders()[i] == OrderStatus::PENDING)
    //     {      
    //     }
        
    // }
}

string SimulateStep::toString() const
{

}

SimulateStep* SimulateStep::clone() const
{

}

SimulateStep* SimulateStep::clone() const
{
    return new SimulateStep(*this);
}



