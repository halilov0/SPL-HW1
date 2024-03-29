#include "Volunteer.h"

// Unlimited Collector Volunteer

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int CoolDown) : Volunteer(id, name), coolDown(CoolDown), timeLeft(CoolDown) {}

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
    return timeLeft <= 0;
}

bool CollectorVolunteer::hasOrdersLeft() const
{
    return true;
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    return (timeLeft == coolDown) && !isBusy();
}

void CollectorVolunteer::acceptOrder(const Order &order)
{
    activeOrderId = order.getId();
    timeLeft = coolDown;
}

string CollectorVolunteer::toString() const
{
    string a = "VolunteerID: " + std::to_string(getId()) + "\n"
             + "isBusy: " + (isBusy() ? "True" : "False") + "\n"
             + "OrderId: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(activeOrderId)) + "\n"
             + "Time Left: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(timeLeft)) + "\n"
             + "OrdersLeft: " + "No Limit";

    return a;
}

string CollectorVolunteer::flag() const
{
    return "c";
}

// Limited Collector Volunteer

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown ,int MaxOrders) : CollectorVolunteer(id, name, coolDown), maxOrders(MaxOrders), ordersLeft(maxOrders) {}

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
    string a = "VolunteerID: " + std::to_string(getId()) + "\n"
             + "isBusy: " + (isBusy() ? "True" : "False") + "\n"
             + "OrderId: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(activeOrderId)) + "\n"
             + "Time Left: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(getTimeLeft())) + "\n"
             + "OrdersLeft: " + std::to_string(ordersLeft);

    return a;     
}