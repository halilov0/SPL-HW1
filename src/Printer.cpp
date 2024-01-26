#pragma once
#include "Action.h"
#include <iostream>
#include "Volunteer.h"

// Print Order Status

PrintOrderStatus::PrintOrderStatus(int id) : orderId(id) {}
void PrintOrderStatus::act(WareHouse &wareHouse)
{
    if (orderId >= wareHouse.getOrdersCounter()) //Assuming!
    {
        error("Order doesn't exist");
        return;
    }
    std::cout << wareHouse.getOrder(orderId).toString() << std::endl;
}

PrintOrderStatus *PrintOrderStatus::clone() const
{
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const
{
}

// Print Customer Status

PrintCustomerStatus::PrintCustomerStatus(int CustomerId) : customerId(CustomerId) {}
void PrintCustomerStatus::act(WareHouse &wareHouse)
{
    bool idExists = false;
    for (int i = 0; i < wareHouse.getCustomers().size(); i++)
    {
        if (wareHouse.getCustomers()[i]->getId() == customerId)
            idExists = true;
    }
    if (!idExists)
    {
        error("Customer doesn't exist");
        return;
    }

    std::cout << "CustomerID: " + customerId << std::endl;
    for (int i = 0; i < wareHouse.getCustomer(customerId).getOrdersIds().size(); i++)
    {
        int orderId = wareHouse.getCustomer(customerId).getOrdersIds()[i];
        string orderStatus = wareHouse.getOrder(orderId).getStatusString();
        std::cout << "OrderID: " + orderId << std::endl;
        std::cout << "OrderStatus: " + orderStatus << std::endl;
    }
    std::cout << "numOrdersLeft: " + wareHouse.getCustomer(customerId).getMaxOrders() - wareHouse.getCustomer(customerId).getNumOrders() << std::endl;
}

PrintCustomerStatus *PrintCustomerStatus::clone() const
{
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const
{
}

//Print Volunteer Status

PrintVolunteerStatus::PrintVolunteerStatus(int id) : VolunteerId(id) {}
void PrintVolunteerStatus::act(WareHouse &wareHouse)
{
    bool idExists = false;
    for (int i = 0; i < wareHouse.getVolunteers().size(); i++)
    {
        if (wareHouse.getVolunteers()[i]->getId() == VolunteerId)
            idExists = true;
    }
    if (!idExists)
    {
        error("Volunteer doesn't exist");
        return;
    }
    std::cout << wareHouse.getVolunteer(VolunteerId).toString() << std::endl;
}

PrintVolunteerStatus *PrintVolunteerStatus::clone() const
{
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const
{

}

// Print Actions Log

PrintActionsLog::PrintActionsLog() {}
void PrintActionsLog::act(WareHouse &wareHouse)
{

}

PrintActionsLog *PrintActionsLog::clone() const
{
    return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const
{

}