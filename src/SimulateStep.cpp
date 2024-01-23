#pragma once
#include "Action.h"
#include <iostream>
using namespace std;

SimulateStep::SimulateStep(int NumOfSteps) : numOfSteps(NumOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse)
{
    for (int i = 0; i < wareHouse.getPendingOrders().size(); i++)
    {
        //We will not use getOrder(ID) because the ID regards to ordersCounter which can refer to an order that is not on pending-order list
        //if (wareHouse.getPendingOrders().get == OrderStatus::PENDING)
        //{
        //    for (int j = 0; j < wareHouse)
        //}
        
    }
}

