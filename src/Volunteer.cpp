#include "Volunteer.h"

Volunteer::Volunteer(int Id, const string &Name) : id(Id), name(Name), activeOrderId(NO_ORDER), completedOrderId(NO_ORDER){}

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
