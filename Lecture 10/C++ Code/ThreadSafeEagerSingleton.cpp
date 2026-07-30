#include<iostream>
#include <mutex>

using namespace std;

class Singleton {
private:
    static Singleton* instance;//What is static member? A static member is a member of a class that is shared by all instances of the class. It is not tied to any specific instance of the class, but rather belongs to the class itself. In this case, the static member 'instance' is used to hold the single instance of the Singleton class.

    Singleton() { 
        cout << "Singleton Constructor Called!" << endl; 
    }
 
public:
    static Singleton* getInstance() {
        return instance;
    }
};
 
// Initialize static members// Why is this thread safe? Because the instance is created at the time of class loading, and class loading is thread safe in C++. So, we don't need to worry about multiple threads creating multiple instances of the singleton class.
Singleton* Singleton::instance = new Singleton();

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout << (s1 == s2) << endl;
}