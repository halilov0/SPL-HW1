#pragma once
#include "Action.h"
#include <iostream>
using namespace std;

SimulateStep::SimulateStep(int NumOfSteps) : numOfSteps(NumOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse)
{
    for (int i = 0; i < wareHouse.getPendingOrders().size(); i++)
    {
        
    }

    for (int i = 0; i < wareHouse.getInProcessOrders().size(); i++)
    {
        Order* order = wareHouse.getInProcessOrders()[i];
        if (order->getStatus() == OrderStatus::COLLECTING)
        {
            
        }
        else 
        {
        }
    }
}

