#pragma once
#include "Order.h"

Order::Order(int Id, int CustomerId, int Distance) : id(Id), customerId(CustomerId), distance(Distance),
status(OrderStatus::PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER) {}

int Order::getId() const
{
    return id;
}

int Order::getCustomerId() const
{
    return customerId;
}

int Order::getCustomerId() const
{
    return customerId;
}

int Order::getCustomerId() const
{
    return customerId;
}

void Order::setStatus(OrderStatus status) 
{
    this->status = status;
}

void Order::setCollectorId(int collectorId)
{
    this->collectorId = collectorId;
} 

void Order::setDriverId(int driverId)
{
    this->driverId = driverId;
}

int Order::getCollectorId() const
{
    return collectorId;
}

int Order::getDriverId() const
{
    return driverId;
}

int Order::getDistance() const
{
    return distance;
}

OrderStatus Order::getStatus() const
{
    return status;
}

const string Order::toString() const
{
    string a = "OrderId: " + std::to_string(getId()) + "\n"
             + "OrderStatus: " + getStatusString() + "\n"
             + "CustomerID: " + std::to_string(getCustomerId()) + "\n"
             + "Collector: " + (getCollectorId() >= 0 ? std::to_string(getCollectorId()) : "None") + "\n" 
             + "Driver: " + (getDriverId() >= 0 ? std::to_string(getDriverId()) : "None");

    return a;
}

string Order::getStatusString() const
{
    if (status == OrderStatus::PENDING)
        return "Pending";
    else if (status == OrderStatus::COLLECTING)
        return "Collecting";
    else if (status == OrderStatus::DELIVERING)
        return "Delivering";
    return "Completed";
}



