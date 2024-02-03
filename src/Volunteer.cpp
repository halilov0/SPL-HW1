#include "Volunteer.h"

Volunteer::Volunteer(int Id, const string &Name) : completedOrderId(NO_ORDER), activeOrderId(NO_ORDER), id(Id), name(Name) {}

int Volunteer::getId() const
{
    return id;
}

const string &Volunteer::getName () const
{
    return name;
}

int Volunteer::getActiveOrderId() const
{
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const
{
    return completedOrderId;
}

bool Volunteer::isBusy() const
{
    return activeOrderId != NO_ORDER;
}
