#pragma once
#include "Action.h"
#include <iostream>
#include "WareHouse.h"
using namespace std;


AddOrder::AddOrder(int id) : customerId(id) {}

void AddOrder::act(WareHouse &wareHouse)
{
    Customer& customer = wareHouse.getCustomer(customerId);
    if(customer.getId() != NO_CUSTOMER && customer.canMakeOrder())
    {
        complete();
        wareHouse.addAction(this);
    }
    else 
        error("Cannot place this order");        
}

string AddOrder::toString() const
{
    return "order " + std::to_string(customerId) + " " + getActionStatusString(); 
}   

AddOrder *AddOrder::clone() const
{
    return new AddOrder(*this);
}