#pragma once
#include "Action.h"
#include <iostream>
using namespace std;

CustomerType getType(string type)
{
    if (type == "Soldier")
        return CustomerType::Soldier;
    return CustomerType::Civilian;
}

AddCustomer::AddCustomer(string CustomerName, string CustomerType, int Distance, int MaxOrders) : customerName(CustomerName), customerType(getType(CustomerType)), distance(Distance), maxOrders(MaxOrders) {}

void AddCustomer::act(WareHouse &wareHouse)
{
    Customer* customer;
    if (customerType == CustomerType::Soldier)
    {
        customer = new SoldierCustomer(wareHouse.getCustomerCounter(), customerName, distance, maxOrders);
        wareHouse.addCustomer(customer);
    }   
    else
    {
        customer = new CivilianCustomer(wareHouse.getCustomerCounter(), customerName, distance, maxOrders);
        wareHouse.addCustomer(customer);
    }
    delete customer; //??
}