#pragma once
#include "Action.h"
#include <iostream>
#include "WareHouse.h"
using namespace std;

CustomerType getType(string type)
{
    if (type == "soldier")
        return CustomerType::Soldier;
    return CustomerType::Civilian;
}

string getString(CustomerType type)
{
    if (type == CustomerType::Soldier)
        return "soldier";
    return "civilian";
}

AddCustomer::AddCustomer(string CustomerName, string CustomerType, int Distance, int MaxOrders) : customerName(CustomerName), customerType(getType(CustomerType)), distance(Distance), maxOrders(MaxOrders) {}

void AddCustomer::act(WareHouse &wareHouse)
{
    complete();
    wareHouse.addAction(this);
}

string AddCustomer::toString() const
{
    return "customer " + customerName + " " + getString(customerType) + " " + std::to_string(distance) + " " + std::to_string(maxOrders) + " " + getActionStatusString();
}

AddCustomer *AddCustomer::clone() const
{
    return new AddCustomer(*this);
}