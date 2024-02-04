#include "Action.h"
#include "WareHouse.h"
using namespace std;


AddOrder::AddOrder(int id) : customerId(id) {}

void AddOrder::act(WareHouse &wareHouse)
{
    Customer& customer = wareHouse.getCustomer(customerId);
    if (customer.getId() != NULL_OBJECT && customer.canMakeOrder())
    {
        complete();
    }
    else 
        error("Cannot place this order");
    wareHouse.addAction(this);       
}

string AddOrder::toString() const
{
    return "order " + to_string(customerId) + " " + getActionStatusString(); 
}   

AddOrder *AddOrder::clone() const
{
    return new AddOrder(*this);
}