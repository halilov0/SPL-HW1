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

#define NULL_OBJECT -1

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
        

        Volunteer& getNotBusyVolunteer(const Order &order, string flag);
        void addVolunteer(Volunteer* volunteer);
        int getOrdersCounter() const;
        int getCustomerCounter() const;
        int getVolunteerCounter() const;
        void removeUselessVolunteers();
        void removeOrder(int id, vector<Order*>& ordersToRemove);

        const vector<Volunteer*>& getVolunteers();
        const vector<Customer*>& getCustomers();
        const vector<Order*>& getPendingOrders();
        const vector<Order*>& getInProcessOrders();
        const vector<Order*>& getCompletedOrders();
        void moveOrder(Order* order, OrderType from, OrderType to);

        // rule of 5
        WareHouse(const WareHouse& other);
        ~WareHouse();       
        WareHouse& operator=(const WareHouse& other);
        WareHouse(WareHouse&& other) noexcept;
        WareHouse& operator=(WareHouse&& other) noexcept;
        
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
        Volunteer* nullV; // fake volunteer  
        Customer* nullC; // fake customer
        Order* nullO; // fake order
};