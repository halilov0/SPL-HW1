#include "Action.h"
#include <iostream>
#include "Volunteer.h"
#include "WareHouse.h"
using namespace std;


PrintOrderStatus::PrintOrderStatus(int id) : orderId(id) {}
void PrintOrderStatus::act(WareHouse &wareHouse)
{
    if (0 <= orderId && orderId < wareHouse.getOrdersCounter()) //Assuming!
    {
        cout << wareHouse.getOrder(orderId).toString() << endl;
        complete();
    }
    else
        error("Order doesn't exist");
    wareHouse.addAction(this);
}

PrintOrderStatus *PrintOrderStatus::clone() const
{
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const
{
    return "orderStatus " + to_string(orderId) + " " + getActionStatusString();
}

// Print Customer Status

PrintCustomerStatus::PrintCustomerStatus(int CustomerId) : customerId(CustomerId) {}
void PrintCustomerStatus::act(WareHouse &wareHouse)
{
    bool idExists = false;
    for (int i = 0; i < (int)wareHouse.getCustomers().size(); i++)
    {
        if (wareHouse.getCustomers()[i]->getId() == customerId)
            idExists = true;
    }
    if (!idExists)
    {
        error("Customer doesn't exist");
    }
    else
    {
        cout << "CustomerID: " << customerId << endl;
        for (int i = 0; i < (int)wareHouse.getCustomer(customerId).getOrdersIds().size(); i++)
        {
            int orderId = wareHouse.getCustomer(customerId).getOrdersIds()[i];
            string orderStatus = wareHouse.getOrder(orderId).getStatusString();
            cout << "OrderID: " << orderId << endl;
            cout << "OrderStatus: " << orderStatus << endl;
        }
        cout << "numOrdersLeft: " << wareHouse.getCustomer(customerId).getMaxOrders() - wareHouse.getCustomer(customerId).getNumOrders() << endl;
        complete();    
    }
    wareHouse.addAction(this);
}

PrintCustomerStatus *PrintCustomerStatus::clone() const
{
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const
{
    return "customerStatus " + to_string(customerId) + " " + getActionStatusString();
}

//Print Volunteer Status

PrintVolunteerStatus::PrintVolunteerStatus(int id) : VolunteerId(id) {}
void PrintVolunteerStatus::act(WareHouse &wareHouse)
{
    bool idExists = false;
    for (int i = 0; i < (int)wareHouse.getVolunteers().size(); i++)
    {
        if (wareHouse.getVolunteers()[i]->getId() == VolunteerId)
            idExists = true;
    }
    if (!idExists)
    {
        error("Volunteer doesn't exist");
    }
    else 
    {
        cout << wareHouse.getVolunteer(VolunteerId).toString() << endl;
        complete();
    }
    wareHouse.addAction(this);
}

PrintVolunteerStatus *PrintVolunteerStatus::clone() const
{
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const
{
    return "volunteerStatus " + to_string(VolunteerId) +  " " + getActionStatusString();
}

// Print Actions Log

PrintActionsLog::PrintActionsLog() {}
void PrintActionsLog::act(WareHouse &wareHouse)
{
	for (int i = 0; i < (int)wareHouse.getActions().size(); i++)
	{
		cout << wareHouse.getActions()[i]->toString() << endl;
	}
    complete();
    wareHouse.addAction(this);
}

PrintActionsLog *PrintActionsLog::clone() const
{
    return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const
{
    return "log " + getActionStatusString();
}