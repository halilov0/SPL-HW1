#pragma once
#include "Action.h"
#include <iostream>
using namespace std;

BaseAction::BaseAction() {}

ActionStatus BaseAction::getStatus() const
{
    return status;
}

void BaseAction::complete() 
{
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg)
{
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
    cout << "ERROR: " + errorMsg << endl;
}

string BaseAction::getErrorMsg() const
{
    return errorMsg;
}

string BaseAction::getActionStatusString() const
{
    if (status == ActionStatus::COMPLETED)
        return "COMPLETED";
    return "ERROR";
}