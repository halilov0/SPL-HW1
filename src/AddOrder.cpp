#pragma once
#include "Action.h"
#include <iostream>
using namespace std;


AddOrder::AddOrder(int id) : customerId(id) {}

void AddOrder::act(WareHouse &wareHouse)
{
    Customer& customer = wareHouse.getCustomer(customerId);
    if(&customer != NULL && customer.canMakeOrder())
    {
        Order* order = new Order(wareHouse.getOrdersCounter(), customerId, customer.getCustomerDistance());
        wareHouse.addOrder(order);
        order = nullptr; //??
    }
    else 
        error("Cannot place this order");        
}

string AddOrder::toString() const
{
    return "order " + std::to_string(customerId) + " " + getActionStatusString(); 
}   