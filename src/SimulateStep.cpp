#pragma once
#include "Action.h"
#include <iostream>
using namespace std;

SimulateStep::SimulateStep(int NumOfSteps) : numOfSteps(NumOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse)
{
    for (int i = 0; i < wareHouse.getActions().size(); i++)
    {
        if (wareHouse.getOrder(i).getStatus() == OrderStatus::PENDING)
        {
            for (int j = 0; j < wareHouse)
        }
    }
}

