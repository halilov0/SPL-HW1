#pragma once
#include "Customer.h"


Customer::Customer(int Id, const string &Name, int LocationDistance, int MaxOrders) : id(Id), name(Name), 
locationDistance(LocationDistance), maxOrders(MaxOrders) {}

//copy constructor
Customer::Customer(Customer* cus) : id(cus->id), name(cus->name), 
locationDistance(cus->locationDistance), maxOrders(cus->maxOrders){}

const string& Customer::getName() const
{
    return name;
}

int Customer::getId() const
{
    return id;
}

int Customer::getCustomerDistance() const
{
    return locationDistance;
}

int Customer::getMaxOrders() const
{
    return maxOrders;
}

int Customer::getNumOrders() const
{
    return ordersId.size();
}

bool Customer::canMakeOrder() const
{
    return (maxOrders>ordersId.size());
}

const vector<int>& Customer::getOrdersIds() const
{
    return ordersId;
}

int Customer::addOrder(int orderId)
{
    if (canMakeOrder())
    {
        ordersId.push_back(orderId);
        return orderId;
    }
    return -1;
}



SoldierCustomer::SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders) :
Customer(id, name, locationDistance, maxOrders) {}

SoldierCustomer* SoldierCustomer::clone() const
{
    return new SoldierCustomer(*this);
}



CivilianCustomer::CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders) :
Customer(id, name, locationDistance, maxOrders) {}

CivilianCustomer* CivilianCustomer::clone() const
{
    return new CivilianCustomer(*this);
}