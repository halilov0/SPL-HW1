#pragma once
#include "Volunteer.h"

DriverVolunteer::DriverVolunteer(int id, const string &name, int MaxDistance, int DistancePerStep) : 
Volunteer(id, name), maxDistance(MaxDistance), distancePerStep(DistancePerStep) {}

DriverVolunteer* DriverVolunteer::clone() const
{
    return new DriverVolunteer(*this);
} 

void DriverVolunteer::step()
{    
    if (decreaseDistanceLeft())
        distanceLeft = maxDistance;
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
    distanceLeft--;
    return (distanceLeft == 0);
}

bool DriverVolunteer::hasOrdersLeft() const
{
    return true;
}

bool DriverVolunteer::canTakeOrder(const Order &order) const
{
    return hasOrdersLeft() && order.getDistance() < maxDistance;
}

void DriverVolunteer::acceptOrder(const Order &order)
{
    distanceLeft = order.getDistance();
}

string DriverVolunteer::toString() const
{
    return fbf;
}


LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int MaxDistance, int DistancePerStep, int MaxOrders) : 
DriverVolunteer(id, name, MaxDistance, DistancePerStep), maxOrders(MaxOrders) {}

LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const
{
    return new LimitedDriverVolunteer(*this);
}

bool LimitedDriverVolunteer::hasOrdersLeft() const
{
    return (ordersLeft>0);
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    return hasOrdersLeft() && order.getDistance() < getMaxDistance();
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
    return bab;   
}