#include <iostream>
using namespace std;

class FlyBehaviour{
    public:
    virtual void fly()=0;
    virtual ~FlyBehaviour(){};
};

class CanFly:public FlyBehaviour{
    public:
    void fly() override{
        cout<<"This Duck can fly!!!"<<endl;
    }
};

class CannotFly:public FlyBehaviour{
    public:
    void fly() override{
        cout<<"This Duck cannot fly...............OOPS"<<endl;
    }
};

class SoundBehaviour{
    public:
    virtual void sound()=0;
    virtual ~SoundBehaviour(){};
};

class QuackSound:public SoundBehaviour{
    public:
    void sound() override{
        cout<<"Quack Quack Quack!!!"<<endl;
    }
};

class SqueakSound:public SoundBehaviour{
    public:
    void sound() override{
        cout<<"Squeak Squeak Squeak!!!"<<endl;
    }
};

class NoSound:public SoundBehaviour{
    public:
    void sound() override{
        cout<<"I can't speak.............."<<endl;
    }
};

class Duck{
    private:
    SoundBehaviour* soundBehaviour;
    FlyBehaviour* flyBehaviour;

    public:
    Duck(SoundBehaviour* soundBehaviour,FlyBehaviour* flyBehaviour){
        this->flyBehaviour=flyBehaviour;
        this->soundBehaviour=soundBehaviour;
    }

    void speak(){
        soundBehaviour->sound();
    }
    void fly(){
        flyBehaviour->fly();
    }

};

class MallardDuck:public Duck{
    public:
    MallardDuck():Duck(new QuackSound(),new CanFly()){}

};

//Rest Done not created only for testing

int main(){
    MallardDuck*mallardDuck=new MallardDuck();

    mallardDuck->fly();
    mallardDuck->speak();

    delete mallardDuck;
    return 0;
};




