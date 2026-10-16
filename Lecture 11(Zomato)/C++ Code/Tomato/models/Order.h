#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include "../strategies/PaymentStrategy.h"
#include "../utils/TimeUtils.h"
using namespace std;

class Order {
protected:
    static int nextOrderId;
    int orderId;
    User* user;
    Restaurant* restaurant;
    vector<MenuItem> items;
    PaymentStrategy* paymentStrategy;
    double total;
    string scheduled;

public:
    Order() {
        user = nullptr;//why null should be null because when an order is created, it may not be immediately associated with a user. The user may be set later when the order is placed or processed. Initializing it to nullptr ensures that we can check if a user has been assigned to the order before proceeding with any operations that require a user.
        restaurant = nullptr;
        paymentStrategy = nullptr;
        total = 0.0;
        scheduled = "";
        orderId = ++nextOrderId;
    }

    virtual ~Order() {
        delete paymentStrategy;
    }

    bool processPayment() {//At this point, C++ does not know whether it will be UPI, Card, Wallet, etc.
        //Then somewhere outside the Order class, somebody does:
        //order->paymentStrategy = new UpiPaymentStrategy("9876543210");
        if (paymentStrategy) {
            paymentStrategy->pay(total);//here 
            return true;
        } else {
            cout << "Please choose a payment mode first" << endl;
            return false;
        }
    }

    virtual string getType() const = 0;

    //Getter and Setters
    int getOrderId() const {
        return orderId;
    }

    void setUser(User* u) {
        user = u;
    }

    User* getUser() const {
        return user;
    }

    void setRestaurant(Restaurant* r) {
        restaurant = r;
    }

    Restaurant* getRestaurant() const {
        return restaurant;
    }

    void setItems(const vector<MenuItem>& its) {
        items = its;
        total = 0;
        for (auto &i : items) {
            total += i.getPrice();
        }
    }

    const vector<MenuItem>& getItems() const {
        return items;
    }

    void setPaymentStrategy(PaymentStrategy* p) {
        paymentStrategy = p;
    }

    void setScheduled(const string& s) {
        scheduled = s;
    }

    string getScheduled() const {
        return scheduled;
    }

    double getTotal() const {
        return total;
    }

    void setTotal(int total) {
        this->total = total;
    }
};

int Order::nextOrderId = 0;

#endif // ORDER_H
