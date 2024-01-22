#pragma once
#include "Action.h"
#include <iostream>
using namespace std;


AddOrder::AddOrder(int id) : customerId(id){}

void AddOrder::act(WareHouse &wareHouse)
{
    Customer c = wareHouse.getCustomer(customerId);
    if(c != NULL && c.canMakeOrder)
    {
        Order* o = new Order(wareHouse.getOrdersCounter(), customerId, c.getCustomerDistance());
        wareHouse.addOrder(o);
        o = nullptr;
    }
    else 
        error("Cannot place this order");        
}