#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ======================
// Notification Component
// ======================

class INotification {
public:
    virtual string getContent() const = 0;
    virtual ~INotification() {}
};

class SimpleNotification : public INotification {
private:
    string text;

public:
    SimpleNotification(const string& text) {
        this->text = text;
    }

    string getContent() const override {
        return text;
    }
};

// ======================
// Decorator Pattern
// ======================

class INotificationDecorator : public INotification {
protected:
    INotification* notification;

public:
    INotificationDecorator(INotification* n) {
        this->notification = n;
    }

    virtual ~INotificationDecorator() {
        delete notification;
    }
};

class TimeStampDecorator : public INotificationDecorator {
public:
    TimeStampDecorator(INotification* n)
        : INotificationDecorator(n) {}

    string getContent() const override {
        return "[2026-07-30 10:00 AM] " + notification->getContent();
    }
};

class SignatureDecorator : public INotificationDecorator {
private:
    string signature;

public:
    SignatureDecorator(INotification* n, const string& signature)
        : INotificationDecorator(n) {
        this->signature = signature;
    }

    string getContent() const override {
        return notification->getContent() +
               "\n\n--\n" + signature;
    }
};

// ======================
// Observer Pattern
// ======================

class IObserver {
public:
    virtual void update() = 0;
    virtual ~IObserver() {}
};

class IObservable {
public:
    virtual void addObserver(IObserver* obs) = 0;
    virtual void removeObserver(IObserver* obs) = 0;
    virtual void notifyObservers() = 0;

    virtual ~IObservable() {}
};

class NotificationObservable : public IObservable {
private:
    vector<IObserver*> observers;
    INotification* currentNotification;

public:
    NotificationObservable() {
        currentNotification = nullptr;
    }

    void addObserver(IObserver* obs) override {
        observers.push_back(obs);
    }

    void removeObserver(IObserver* obs) override {
        observers.erase(
            remove(observers.begin(), observers.end(), obs),
            observers.end());
    }

    void notifyObservers() override {
        for (auto observer : observers) {
            observer->update();
        }
    }

    void setNotification(INotification* notification) {
        if (currentNotification != nullptr) {
            delete currentNotification;
        }

        currentNotification = notification;
        notifyObservers();
    }

    string getNotificationContent() {
        if (currentNotification == nullptr) {
            return "";
        }

        return currentNotification->getContent();
    }

    ~NotificationObservable() {
        delete currentNotification;
    }
};

// ======================
// Logger Observer
// ======================

class Logger : public IObserver {
private:
    NotificationObservable* observable;

public:
    Logger(NotificationObservable* observable) {
        this->observable = observable;
    }

    void update() override {
        cout << "\n===== LOGGER =====\n";
        cout << observable->getNotificationContent() << endl;
    }
};

// ======================
// Strategy Pattern
// ======================

class INotificationStrategy {
public:
    virtual void sendNotification(string content) = 0;
    virtual ~INotificationStrategy() {}
};

class EmailStrategy : public INotificationStrategy {
private:
    string emailId;

public:
    EmailStrategy(const string& emailId) {
        this->emailId = emailId;
    }

    void sendNotification(string content) override {
        cout << "\n[EMAIL -> " << emailId << "]\n";
        cout << content << endl;
    }
};

class SMSStrategy : public INotificationStrategy {
private:
    string mobileNumber;

public:
    SMSStrategy(const string& mobileNumber) {
        this->mobileNumber = mobileNumber;
    }

    void sendNotification(string content) override {
        cout << "\n[SMS -> " << mobileNumber << "]\n";
        cout << content << endl;
    }
};

class PopUpStrategy : public INotificationStrategy {
public:
    void sendNotification(string content) override {
        cout << "\n[POPUP]\n";
        cout << content << endl;
    }
};

// ======================
// Notification Engine
// ======================

class NotificationEngine : public IObserver {
private:
    NotificationObservable* notificationObservable;
    vector<INotificationStrategy*> notificationStrategies;

public:
    NotificationEngine(NotificationObservable* observable) {
        this->notificationObservable = observable;
    }

    void addNotificationStrategy(INotificationStrategy* strategy) {
        notificationStrategies.push_back(strategy);
    }

    void update() override {
        string content =
            notificationObservable->getNotificationContent();

        for (auto strategy : notificationStrategies) {
            strategy->sendNotification(content);
        }
    }

    ~NotificationEngine() {
        for (auto strategy : notificationStrategies) {
            delete strategy;
        }
    }
};

// ======================
// Singleton Service
// ======================

class NotificationService {
private:
    NotificationObservable* observable;

    static NotificationService* instance;

    NotificationService() {
        observable = new NotificationObservable();
    }

public:
    static NotificationService* getInstance() {
        if (instance == nullptr) {
            instance = new NotificationService();
        }

        return instance;
    }

    NotificationObservable* getObservable() {
        return observable;
    }

    void sendNotification(INotification* notification) {
        observable->setNotification(notification);
    }

    ~NotificationService() {
        delete observable;
    }
};

NotificationService* NotificationService::instance = nullptr;

// ======================
// Main
// ======================

int main() {

    NotificationService* notificationService =
        NotificationService::getInstance();

    NotificationObservable* notificationObservable =
        notificationService->getObservable();

    Logger* logger =
        new Logger(notificationObservable);

    NotificationEngine* notificationEngine =
        new NotificationEngine(notificationObservable);

    notificationEngine->addNotificationStrategy(
        new EmailStrategy("random.person@gmail.com"));

    notificationEngine->addNotificationStrategy(
        new SMSStrategy("+91 9876543210"));

    notificationEngine->addNotificationStrategy(
        new PopUpStrategy());

    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    INotification* notification =
        new SimpleNotification("Your order has been cancelled");

    notification =
        new TimeStampDecorator(notification);

    notification =
        new SignatureDecorator(
            notification,
            "Piyush Kumar");

    notificationService->sendNotification(notification);

    delete logger;
    delete notificationEngine;

    return 0;
}