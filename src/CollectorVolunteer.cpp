#pragma once
#include "Volunteer.h"

// Unlimited Collector Volunteer

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int CoolDown) : Volunteer(id, name), coolDown(CoolDown), timeLeft(CoolDown) {}

CollectorVolunteer::CollectorVolunteer(const CollectorVolunteer& cVol) : Volunteer(cVol.getId(), cVol.getName()), coolDown(cVol.coolDown), timeLeft(cVol.coolDown) {}

CollectorVolunteer* CollectorVolunteer::clone() const
{
    return new CollectorVolunteer(*this);
} 

void CollectorVolunteer::step()
{    
    if (decreaseCoolDown())
    {
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
        timeLeft = coolDown;
    }
}

int CollectorVolunteer::getCoolDown() const
{
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const
{
    return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown()
{
    timeLeft--;
    return timeLeft == 0;
}

bool CollectorVolunteer::hasOrdersLeft() const
{
    return true;
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    //Should we consider "is busy"?
    return timeLeft == coolDown;
}

void CollectorVolunteer::acceptOrder(const Order &order)
{
    activeOrderId = order.getId();
    timeLeft = coolDown;
}

string CollectorVolunteer::toString() const
{
    string a = "VolunteerID: " + std::to_string(getId()) + "\n"
             + "isBusy: " + std::to_string(isBusy()) + "\n"
             + "OrderId: " + std::to_string(activeOrderId) + "\n"
             + "Time Left: " + std::to_string(timeLeft);
    return a;
}

// Limited Collector Volunteer

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown ,int MaxOrders) : CollectorVolunteer(id, name, coolDown), maxOrders(MaxOrders) {}

LimitedCollectorVolunteer::LimitedCollectorVolunteer(const LimitedCollectorVolunteer& cVol) : CollectorVolunteer(cVol.getId(), cVol.getName(), cVol.getCoolDown()), maxOrders(cVol.maxOrders) {}

LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return hasOrdersLeft() && CollectorVolunteer::canTakeOrder(order);
}


void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    CollectorVolunteer::acceptOrder(order);
    ordersLeft--;
}

int LimitedCollectorVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const
{
    string s = CollectorVolunteer::toString() + "\n" + "ordersLeft: " + std::to_string(ordersLeft);
    return s;     
}