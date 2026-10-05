#include <iostream>
using namespace std;

class PaymentStrategy{
    public:
    virtual void pay()=0;
    virtual ~PaymentStrategy(){}
};

class UpiPayemt: public PaymentStrategy{
    void pay() override{
        cout<<"UPI Payment is done!!!"<<endl;
    }
};

class CashPayemt: public PaymentStrategy{
    void pay() override{
        cout<<"Cash Payment is done!!!"<<endl;
    }
};

class PayPalPayemt: public PaymentStrategy{
    void pay() override{
        cout<<"PayPal Payment is done!!!"<<endl;
    }
};

class PaymentService{
    private:
    PaymentStrategy*paymentStrategy;

    public:
    PaymentService(PaymentStrategy*paymentStrategy){
        this->paymentStrategy=paymentStrategy;
    }

    void payment(){
        paymentStrategy->pay();

    }
    
};

int main(){
    PaymentStrategy*paymentStrategy=new UpiPayemt();
    PaymentService*paymentService=new PaymentService(paymentStrategy);
    paymentService->payment();

    delete paymentService;
    delete paymentStrategy;
    return 0;
};