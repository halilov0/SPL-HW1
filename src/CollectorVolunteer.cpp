#pragma once
#include "Volunteer.h"

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int CoolDown) : Volunteer(id, name), coolDown(CoolDown), timeLeft(CoolDown) {}

CollectorVolunteer::CollectorVolunteer(const CollectorVolunteer& cVol) : Volunteer(cVol.getId(), cVol.getName()), coolDown(cVol.coolDown), timeLeft(cVol.coolDown) {}

CollectorVolunteer* CollectorVolunteer::clone() const
{
    return new CollectorVolunteer(*this);
} 

void CollectorVolunteer::step()
{    
    if (decreaseCoolDown())
        timeLeft = coolDown;
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
    timeLeft = timeLeft - 1;
    return (timeLeft == 0);
}

bool CollectorVolunteer::hasOrdersLeft() const
{
    return (1==1);
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    return (timeLeft == coolDown);
}

void CollectorVolunteer::acceptOrder(const Order &order)
{
}

string CollectorVolunteer::toString() const
{
    return fbf;
}


LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown ,int MaxOrders) : CollectorVolunteer(id, name, coolDown), maxOrders(MaxOrders) {}

LimitedCollectorVolunteer::LimitedCollectorVolunteer(const LimitedCollectorVolunteer& cVol) : CollectorVolunteer(cVol.getId(), cVol.getName(), cVol.getCoolDown()), maxOrders(cVol.maxOrders) {}

LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return (ordersLeft>0);
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return (hasOrdersLeft);
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    ordersLeft = ordersLeft - 1;
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
    
}