#pragma once
#include "Action.h"
#include <iostream>
#include "WareHouse.h"

extern WareHouse* backup;

Close::Close() {}
void Close::act(WareHouse &wareHouse) 
{
    for (int customerId = 0; customerId < wareHouse.getCustomers().size(); customerId++)
    {
        for (int i = 0; i < wareHouse.getCustomer(customerId).getOrdersIds().size(); i++)
        {
            int orderId = wareHouse.getCustomer(customerId).getOrdersIds()[i];
            string orderStatus = wareHouse.getOrder(orderId).getStatusString();
            std::cout << "OrderID: " << orderId << " CustomerID: " << customerId << " OrderStatus: " << orderStatus << std::endl;
        }
    }
    wareHouse.addAction(this);
    wareHouse.close();
}
Close *Close::clone() const {
    return new Close(*this);
}
string Close::toString() const 
{
    return "close " + getActionStatusString();
}



BackupWareHouse::BackupWareHouse() {}
void BackupWareHouse::act(WareHouse &wareHouse)
{
    backup = new WareHouse(wareHouse);
    wareHouse.addAction(this);
}

BackupWareHouse *BackupWareHouse::clone() const {
    return new BackupWareHouse(*this);
}
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
void RestoreWareHouse::act(WareHouse &wareHouse) {
    if(backup == nullptr)
        error("No backup available");
    else
        wareHouse = (*backup);
    wareHouse.addAction(this);
}
RestoreWareHouse *RestoreWareHouse::clone() const {
    return new RestoreWareHouse(*this);
}
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