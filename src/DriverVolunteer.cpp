#pragma once
#include "Volunteer.h"

// Unlimited Driver Volunteer

DriverVolunteer::DriverVolunteer(int id, const string &name, int MaxDistance, int DistancePerStep) : 
Volunteer(id, name), maxDistance(MaxDistance), distancePerStep(DistancePerStep) {}

DriverVolunteer* DriverVolunteer::clone() const
{
    return new DriverVolunteer(*this);
} 

void DriverVolunteer::step()
{    
    if (decreaseDistanceLeft())
    {
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
        distanceLeft = 0;
    }
}

int DriverVolunteer::getDistanceLeft() const
{
    return distanceLeft;
}

int DriverVolunteer::getMaxDistance() const
{
    return maxDistance;
}

bool DriverVolunteer::decreaseDistanceLeft()
{
    distanceLeft -= distancePerStep;
    return distanceLeft <= 0;
}

bool DriverVolunteer::hasOrdersLeft() const
{
    return true;
}

bool DriverVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy() && order.getDistance() <= maxDistance;
}

void DriverVolunteer::acceptOrder(const Order &order)
{
    activeOrderId = order.getId();
    distanceLeft = order.getDistance();
}

string DriverVolunteer::toString() const
{
    string a = "VolunteerID: " + std::to_string(getId()) + "\n"
             + "isBusy: " + std::to_string(isBusy()) + "\n"
             + "OrderId: " + std::to_string(activeOrderId) + "\n"
             + "Distance Left: " + std::to_string(distanceLeft);
    return a;
}

string DriverVolunteer::flag() const
{
    return "d";
}

// Limited Driver Volunteer

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int MaxDistance, int DistancePerStep, int MaxOrders) : 
DriverVolunteer(id, name, MaxDistance, DistancePerStep), maxOrders(MaxOrders) {}

LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const
{
    return new LimitedDriverVolunteer(*this);
}

bool LimitedDriverVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    return hasOrdersLeft() && DriverVolunteer::canTakeOrder(order);
}

void LimitedDriverVolunteer::acceptOrder(const Order &order)
{
    DriverVolunteer::acceptOrder(order);
    ordersLeft--;
}

int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}

string LimitedDriverVolunteer::toString() const
{
    string s = DriverVolunteer::toString() + "\n" + "ordersLeft: " + std::to_string(ordersLeft);   
}