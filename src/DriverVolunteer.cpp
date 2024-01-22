#pragma once
#include "Volunteer.h"

DriverVolunteer::DriverVolunteer(int id, const string &name, int MaxDistance, int DistancePerStep) : Volunteer(id, name), maxDistance(MaxDistance), distancePerStep(DistancePerStep) {}

DriverVolunteer::DriverVolunteer(const DriverVolunteer& dVol) : Volunteer(dVol.getId(), dVol.getName()), maxDistance(MaxDistance), distancePerStep(DistancePerStep) {}

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
    distranceLeft = order.getDistance();
    ordersLeft--;
}

string DriverVolunteer::toString() const
{
    return fbf;
}


LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int MaxDistance, int DistancePerStep, int MaxOrders) : DriverVolunteer(int id, const string &name, int MaxDistance, int DistancePerStep), maxOrders(MaxOrders) {}

LimitedDriverVolunteer::LimitedDriverVolunteer(const LimitedDriverVolunteer& dVol) : DriverVolunteer(dVol.getId(), dVol.getName(), dVol.getMaxDistance(), dVol.getDistancePerStep()), maxOrders(dVol.maxOrders) {}

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
    return hasOrdersLeft() && order.getDistance() < maxDistance;
}

void LimitedDriverVolunteer::acceptOrder(const Order &order)
{
    distranceLeft = order.getDistance();
    ordersLeft--;
}

int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedDriverVolunteer::getDistancePerStep() const
{
    return distancePerStep;
}

string LimitedDriverVolunteer::toString() const
{   
}