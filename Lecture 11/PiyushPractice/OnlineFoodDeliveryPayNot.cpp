#include<iostream>
#include<vector>
using namespace std;

class PaymentStartergy{
    public:
    virtual void pay()=0;
    virtual ~PaymentStartergy(){};
};

class UpiPayemnt: public PaymentStartergy{
    public:
    void pay() override{
        cout<<"UPI payment done"<<endl;
    }
};

class CardPayemnt: public PaymentStartergy{
    public:
    void pay() override{
        cout<<"Card payment done"<<endl;
    }
};

class CashPayemnt: public PaymentStartergy{
    public:
    void pay() override{
        cout<<"Cash payment done"<<endl;
    }
};

class Notification{
    public:
    virtual void Notify()=0;
    virtual ~Notification(){};
};

class EmailNotification: public Notification{
    public:
    void Notify() override{
        cout<<"Email:- Order has been placed!!"<<endl;
    }
};

class SMSNotification: public Notification{
    public:
    void Notify() override{
        cout<<"SMS:- Order has been placed!!"<<endl;
    }
};

class PUSHNotification: public Notification{
    public:
    void Notify() override{
        cout<<"PUSH:- Order has been placed!!"<<endl;
    }
};

class NotificationFactory{
    public:
    Notification* CreateNotification(const string& type){
        if(type=="SMS"){
            return new SMSNotification();
        }
        else if(type=="Email"){
            return new EmailNotification();
        }
        else if(type=="PUSH"){
            return new PUSHNotification();
        }
        else{
            return nullptr;
    }
    }

};

class Logger{
    private:
    static Logger* instance;
    Logger(){
        cout<<"Logger Generated"<<endl;
    }
    vector<string>logs;
    public:
    static Logger* getInstance(){
        if(instance==nullptr){
            instance= new Logger();
        };
        return instance;
    }

    void pushlog(const string& msg){
        logs.push_back(msg);
        cout<<"MESSAGE:-"<<msg<<endl;
    };

    void getLogs(){
        for(int i=0;i<logs.size();i++){
            cout<<logs[i]<<endl;
        }
    };
};

Logger* Logger::instance=nullptr;

class CheckoutService{
    private:
    PaymentStartergy *paymentStartergy;
    Logger*logger;

    public:
    CheckoutService(PaymentStartergy*paymentStartergy){
        this->paymentStartergy=paymentStartergy;
        this->logger=Logger::getInstance();
    };

    void payment(){
        logger->pushlog("Payment Started");
        paymentStartergy->pay();
        logger->pushlog("Payment Success");
        NotificationFactory factory;//becayse we actually know what the type of notification is, we can create the object here itself
        //it will be deleted itself after the function is executed, so we don't have to worry about deleting it

        Notification *notification= factory.CreateNotification("SMS");//here beacuse we decide in runtime what type of notification we want to send,
        // we can use the factory design pattern to create the object and then call the notify function on it

        if(notification){
            notification->Notify();
            logger->pushlog("Notification Sent");
        };
        
      

        delete notification;
    };

};

int main(){
    PaymentStartergy* paymentStartergy=new UpiPayemnt();
    CheckoutService* checkoutService=new CheckoutService(paymentStartergy);
    checkoutService->payment();
    delete checkoutService;
    delete paymentStartergy;
}