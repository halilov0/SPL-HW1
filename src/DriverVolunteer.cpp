#include "Volunteer.h"


DriverVolunteer::DriverVolunteer(int id, const string &name, int MaxDistance, int DistancePerStep) : 
Volunteer(id, name), maxDistance(MaxDistance), distancePerStep(DistancePerStep), distanceLeft(maxDistance) {}

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
        // DistanceLeft can be negative so here we ensure it is not
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
             + "isBusy: " + (isBusy() ? "True" : "False") + "\n"
             + "OrderId: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(activeOrderId)) + "\n"
             + "Time Left: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(distanceLeft)) + "\n" //Yes, it is *Time Left* (according to the pdf)
             + "OrdersLeft: " + "No Limit"; 
    return a;
}

string DriverVolunteer::flag() const
{
    return "d";
}

// Limited Driver Volunteer

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int MaxDistance, int DistancePerStep, int MaxOrders) : 
DriverVolunteer(id, name, MaxDistance, DistancePerStep), maxOrders(MaxOrders), ordersLeft(maxOrders) {}

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
    string a = "VolunteerID: " + std::to_string(getId()) + "\n"
             + "isBusy: " + (isBusy() ? "True" : "False") + "\n"
             + "OrderId: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(activeOrderId)) + "\n"
             + "Time Left: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(getDistanceLeft())) + "\n" //Yes, it is *Time Left* (according to the pdf)
             + "OrdersLeft: " + std::to_string(ordersLeft); 
    return a;}