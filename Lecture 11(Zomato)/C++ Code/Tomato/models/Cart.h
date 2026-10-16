#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include <string>
#include "../models/MenuItem.h"
#include "../models/Restaurant.h"

using namespace std;

class Cart {
private:
    Restaurant* restaurant;
    vector<MenuItem> items;//here why not use pointer? because we want to store the actual items in the cart, not just pointers to them. Using a vector of MenuItem objects allows us to easily manage the items in the cart, including adding, removing, and calculating the total cost. If we used pointers, we would have to manage memory allocation and deallocation, which could lead to memory leaks or dangling pointers if not handled correctly. By using a vector of objects, we can take advantage of automatic memory management provided by C++'s standard library.

public:
    Cart() {
        restaurant = nullptr;
    }

    void addItem(const MenuItem& item) {
        if (!restaurant) {
            cerr << "Cart: Set a restaurant before adding items." << endl;
            return;
        }
        items.push_back(item);
    }

    double getTotalCost() const {
        double sum = 0;
        for (const auto& it : items) {
            sum += it.getPrice();
        }
        return sum;
    }

    bool isEmpty() {
        return (!restaurant || items.empty());
    }

    void clear() {
        items.clear();
        restaurant = nullptr;
    }

    // Getters and Setters
    void setRestaurant(Restaurant* r) {
        restaurant = r;
    }

    Restaurant* getRestaurant() const {
        return restaurant;
    }

    const vector<MenuItem>& getItems() const {
        return items;
    }
};

#endif // CART_H
