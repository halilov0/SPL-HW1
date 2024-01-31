#pragma once
#include "Action.h"
#include <iostream>
#include "WareHouse.h"


Close::Close() {}
void Close::act(WareHouse &wareHouse) 
{
    for (int customerId = 0; customerId < wareHouse.getCustomers().size(); customerId++)
    {
        for (int i = 0; i < wareHouse.getCustomer(customerId).getOrdersIds().size(); i++)
        {
            int orderId = wareHouse.getCustomer(customerId).getOrdersIds()[i];
            string orderStatus = wareHouse.getOrder(orderId).getStatusString();
            std::cout << "OrderID: " + orderId << "CustomerID: " + customerId << "OrderStatus: " + orderStatus << std::endl;
        }
    }
}
Close *Close::clone() const {}
string Close::toString() const 
{
    return "close " + getActionStatusString();
}


BackupWareHouse::BackupWareHouse() {}
void BackupWareHouse::act(WareHouse &wareHouse)
{
    //wareHouse.
}

BackupWareHouse *BackupWareHouse::clone() const {}
string BackupWareHouse::toString() const
{
    string s;
    if (getStatus() == ActionStatus::COMPLETED)
    {
        s = "backup COMPLETED";
    }
    else 
        s = getErrorMsg();
    return s;
}


RestoreWareHouse::RestoreWareHouse() {}
void RestoreWareHouse::act(WareHouse &wareHouse) {}
RestoreWareHouse *RestoreWareHouse::clone() const {}
string RestoreWareHouse::toString() const 
{
    string s;
    if (getStatus() == ActionStatus::COMPLETED)
    {
        s = "restore COMPLETED";
    }
    else 
        s = getErrorMsg();
    return s;
}