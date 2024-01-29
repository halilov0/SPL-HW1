#pragma once
#include <string>
#include <vector>

#include "Order.h"
#include "Customer.h"

class BaseAction;
class Volunteer;

enum class OrderType {
    PENDING,
    INPROCESS,
    COMPLETED
};

//Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const std::string &configFilePath);
        void start();
        void addOrder(Order* order);
        void addCustomer(Customer* customer);
        void addAction(BaseAction* action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        void close();
        void open();
        

        Volunteer& getNotBusyDriver(const Order &order);
        Volunteer &getNotBusyCollector(const Order &order);
        void addCustomer(Customer* customer);
        void addVolunteer(Volunteer* volunteer);
        int getOrdersCounter() const;
        int getCustomerCounter() const;
        int getVolunteerCounter() const;
        void removeVolunteer(int id);

        const vector<Volunteer*>& getVolunteers();
        const vector<Customer*>& getCustomers();
        const vector<Order*>& getPendingOrders();
        const vector<Order*>& getInProcessOrders();
        const vector<Order*>& getCompletedOrders();
        void moveOrder(const Order &order, OrderType from, OrderType to);

        
    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int ordersCounter;
        DriverVolunteer* dv; // default 
        CollectorVolunteer* cv; // default
};