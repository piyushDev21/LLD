#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "Cart.h"
using namespace std;

class User{
    private:
        int userId;
        string name;
        string address;
        Cart* cart;//why * is used here?->anser: The asterisk (*) is used here to declare cart as a pointer to a Cart object. This allows for dynamic memory allocation and management of the Cart instance, enabling the User class to create, modify, and delete the Cart object as needed during runtime.

    public:
        User(int userId, const string& name, const string& address) {
            this->userId = userId;
            this->name = name;
            this->address = address;
            cart = new Cart();
        }

        ~User() {
            delete cart;
        }

        // Getters and Setters
        string getName() const {
            return name;
        }

        void setName(const string &n) {
            name = n;
        }

        string getAddress() const {
            return address;
        }

        void setAddress(const string &a) {
            address = a;
        }

        Cart* getCart() const {
            return cart;
        }
};