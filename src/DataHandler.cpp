#include "Action.h"
#include <iostream>
#include "WareHouse.h"

extern WareHouse* backup;

Close::Close() {}
void Close::act(WareHouse &wareHouse) 
{
    for (int customerId = 0; customerId < (int)wareHouse.getCustomers().size(); customerId++)
    {
        for (int i = 0; i < (int)wareHouse.getCustomer(customerId).getOrdersIds().size(); i++)
        {
            int orderId = wareHouse.getCustomer(customerId).getOrdersIds()[i];
            string orderStatus = wareHouse.getOrder(orderId).getStatusString();
            std::cout << "OrderID: " << orderId << " CustomerID: " << customerId << " OrderStatus: " << orderStatus << std::endl;
        }
    }
    complete();
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
    if (backup != nullptr)
        delete backup;
    backup = new WareHouse(wareHouse);
    complete();
    wareHouse.addAction(this);
}

BackupWareHouse *BackupWareHouse::clone() const {
    return new BackupWareHouse(*this);
}
string BackupWareHouse::toString() const
{
    return "backup " + getActionStatusString(); 
}


RestoreWareHouse::RestoreWareHouse() {}
void RestoreWareHouse::act(WareHouse &wareHouse) {
    if(backup == nullptr)
        error("No backup available");
    else
    {
        wareHouse = (*backup);
        complete();
    }
    wareHouse.addAction(this);
}
RestoreWareHouse *RestoreWareHouse::clone() const {
    return new RestoreWareHouse(*this);
}
string RestoreWareHouse::toString() const 
{
    return "restore " + getActionStatusString();
}