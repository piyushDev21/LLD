#include <iostream>
#include <string>
using namespace std;

class VendingMachine;

class NoCoinState;
class HasCoinState;
class DispenseState;
class SoldOutState;

class VendingState{
    public:
    virtual VendingState* insertCoin(VendingMachine * machine, int coin)=0;
    virtual VendingState* selectItem(VendingMachine * machine)=0;
    virtual VendingState* dispense(VendingMachine * machine)=0;
    virtual VendingState* returnCoin(VendingMachine * machine)=0;
    virtual VendingState* refill(VendingMachine * machine, int quantity)=0;
    virtual string getStateName()=0;
};

class VendingMachine{
    private:
    VendingState * currentState;


    VendingState* noCoinState;
    VendingState* hasCoinState;
    VendingState* dispenseState;
    VendingState* soldOutState;

    int itemCount;
    int itemPrice;
    int insertedCoins;

    public:

    VendingMachine(int itemCount,int itemPrice);

    void insertCoin(int coin);
    void selectItem();
    void dispense();
    void returnCoin();
    void refill(int quantity);
    void printStatus();

    VendingState* getNoCoinState() { 
        return noCoinState;
    }
    VendingState* getHasCoinState() { 
        return hasCoinState;
    }
    VendingState* getDispenseState() { 
        return dispenseState; 
    }
    VendingState* getSoldOutState() { 
        return soldOutState;
    }

    int getItemCount() { 
        return itemCount; //here why not use this->itemCount? because
    }
    void decrementItemCount() { 
        itemCount--; 
    }
    void incrementItemCount(int count = 1) {
        itemCount += count;
    }
    int getInsertedCoin() { 
        return insertedCoins;
    }
    void setInsertedCoin(int coin) { 
        insertedCoins = coin;
    }
    void addCoin(int coin) { 
        insertedCoins += coin;
    }
    int getPrice() {
        return this->itemPrice;//why use this->itemPrice? because here we
    }
    void setPrice(int itemPrice) {
        this->itemPrice = itemPrice;
    }


};

class NoCoinState : public VendingState{
    public:
    VendingState* insertCoin(VendingMachine* machine, int coins) override{
        machine->setInsertedCoin(coins);
        cout<<"Coin has been inserted"<<endl;
        return machine->getHasCoinState();
    }

    VendingState* selectItem(VendingMachine* machine) override{
        cout<<"Insert Coin first"<<endl;
        return machine->getNoCoinState();

    }

    VendingState* dispense(VendingMachine* machine) override{
        cout<<"Insert Coin first and select the Item"<<endl;
        return machine->getNoCoinState();
    }

    VendingState* returnCoin(VendingMachine* machine) override{
        cout<<"No coin was inserted"<<endl;
        return machine->getNoCoinState();
    }
    
    VendingState* refill(VendingMachine* machine,int quantity) override{
        machine->incrementItemCount(quantity);
        cout<<"Item refilled"<<endl;
        return machine->getNoCoinState();
    }

    string getStateName()override{
        return "NO_COIN";
    }

};

class HasCoinState : public VendingState{
    public:
    VendingState* insertCoin(VendingMachine* machine, int coins) override{
        machine->setInsertedCoin(coins);
        cout<<"additional Coin has been inserted. Now the totla amount added is "<< machine->getInsertedCoin()<<endl;
        return machine->getHasCoinState();
    }

    VendingState* selectItem(VendingMachine* machine) override{
        if(machine->getInsertedCoin()>= machine->getPrice()){
            cout<<"Item selected..... Dispensing....."<<endl;
            
            int change=machine->getInsertedCoin()>= machine->getPrice();
            if(change>0){
                cout<<"Change returned is "<< change<<endl;

            }
            machine->setInsertedCoin(0);
            return machine->getDispenseState();

        }
        else{
            int needed=machine->getPrice()-machine->getInsertedCoin();
            cout<<"Insufficient balance. Need Rs "<< needed<<" more"<<endl;
            return machine->getHasCoinState();
        }
    }

    VendingState* dispense(VendingMachine* machine) override{
        cout<<"Please select and Item first"<<endl;
        return machine->getHasCoinState();
    }

    VendingState* returnCoin(VendingMachine* machine) override{
        int coin=machine->getInsertedCoin();
        cout<<"Amount returned "<<coin<<". Please check the coin tray in your right!"<<endl;
        machine->setInsertedCoin(0);
        return machine->getNoCoinState();
    }
    
    VendingState* refill(VendingMachine* machine,int quantity) override{
        cout<<"Can't refill when the coin is inserted"<<endl;
        return machine->getNoCoinState();
    }

    string getStateName()override{
        return "HAS_COIN";
    }

};

class DispenseState : public VendingState{
    public:
    VendingState* insertCoin(VendingMachine* machine, int coins) override{
        
        cout<<"Coin cannot be inserted at this state. Please collect your coin "<<endl;
        return machine->getDispenseState();
    }

    VendingState* selectItem(VendingMachine* machine) override{
        cout << "Already dispensing item. Please wait." <<endl;
        return machine->getDispenseState(); // Stay in same state
    }

    VendingState* dispense(VendingMachine* machine) override{
        cout<<"Dispencing"<<endl;
        machine->decrementItemCount();
        if(machine->getItemCount()>0){
            return machine->getNoCoinState();
        }
        else{
            cout<<"Machine is now sold out"<<endl;
            return machine->getSoldOutState();
        }
    }

    VendingState* returnCoin(VendingMachine* machine) override {
       cout << "Cannot return coin while dispensing item!" <<endl;
        return machine->getDispenseState(); // Stay in same state
    }
    
    VendingState* refill(VendingMachine* machine, int quantity) override {
        cout << "Can't refil in this state" <<endl;
        return machine->getDispenseState(); // Stay in same state
    }

    string getStateName()override{
        return "DISPENSING";
    }

};

class SoldOutState : public VendingState{ 
    public:
    VendingState* insertCoin(VendingMachine* machine, int coins) override{
        cout<<"Machine is sold out. Please collect your coin "<<endl;
        return machine->getSoldOutState();
    }

    VendingState* selectItem(VendingMachine* machine) override{
        cout << "Machine is sold out." <<endl;
        return machine->getSoldOutState();
    }

    VendingState* dispense(VendingMachine* machine) override{
        cout << "Machine is sold out." <<endl;
        return machine->getSoldOutState();
    }

    VendingState* returnCoin(VendingMachine* machine) override {
       cout << "Machine is sold out. No coin inserted" <<endl;
        return machine->getSoldOutState();
    }
    
    VendingState* refill(VendingMachine* machine, int quantity) override {
        machine->incrementItemCount(quantity);
        cout << "Refilling" <<endl;
        return machine->getNoCoinState(); // Stay in same state
    }

    string getStateName()override{
        return "SOLD_OUT";
    }

};


VendingMachine::VendingMachine(int itemCount,int itemPrice){
    this->itemCount=itemCount;
    this->itemPrice=itemPrice;
    this->insertedCoins=0;

    noCoinState=new NoCoinState();
    hasCoinState=new HasCoinState();
    dispenseState=new DispenseState();
    soldOutState=new SoldOutState();

    if(itemCount>0){
        this->currentState=noCoinState;//but I did not declare currentState as NoCoinState, I declared it as VendingState* currentState; so how can I assign it to NoCoinState? because NoCoinState is a subclass of VendingState, so we can assign it to VendingState* pointer.
    }
    else{
        this->currentState=soldOutState;
    }
}

void VendingMachine::insertCoin(int coin) {
    currentState = currentState->insertCoin(this, coin);
}

void VendingMachine::selectItem() {
    currentState = currentState->selectItem(this);
}

void VendingMachine::dispense() {
    currentState = currentState->dispense(this);
}

void VendingMachine::returnCoin() {
    currentState = currentState->returnCoin(this);
}

void VendingMachine::refill(int quantity) {
    currentState = currentState->refill(this, quantity);
}

void VendingMachine::printStatus() {
    cout << "\n--- Vending Machine Status ---" << endl;
    cout << "Items remaining: " << itemCount << endl;
    cout << "Inserted coin: Rs " << insertedCoins << endl;
    cout << "Current state: " << currentState->getStateName() << endl << endl;
}

int main(){
    cout<<"COKE vending machine"<<endl;
    int itemCount=2;
    int itemPrice=40;
    VendingMachine* machine=new VendingMachine(itemCount,itemPrice);

    // Test scenarios - each operation potentially changes state
    cout << "1. Trying to select item without coin:" <<endl;
    machine->selectItem();  // Should ask for coin, no state change
    machine->printStatus();
    
    cout << "2. Inserting coin:" <<endl;
    machine->insertCoin(10);  // State changes to HAS_COIN
    machine->printStatus();
    
    cout << "3. Selecting item with insufficient funds:" <<endl;
    machine->selectItem();  // Insufficient funds, stays in HAS_COIN
    machine->printStatus();
    
    cout << "4. Adding more coins:" <<endl;
    machine->insertCoin(10);  // Add more money, stays in HAS_COIN
    machine->printStatus();
    
    cout << "5. Selecting item Now" <<endl;
    machine->selectItem();  // State changes to SOLD
    machine->printStatus();
    
    cout << "6. Dispensing item:" <<endl;
    machine->dispense(); // State changes to NO_COIN (items remaining)
    machine->printStatus();
    
    cout << "7. Buying last item:" <<endl;
    machine->insertCoin(20);  // State changes to HAS_COIN
    machine->selectItem();  // State changes to SOLD
    machine->dispense(); // State changes to SOLD_OUT (no items left)
    machine->printStatus();
    
    // cout << "8. Trying to use sold out machine:" <<endl;
    // machine.insertCoin(5);  // Coin returned, stays in SOLD_OUT

    // cout << "9. Trying to use sold out machine:" <<endl;
    // machine.refill(2);
    // machine.printStatus(); // State changes NO_COIN
    
    return 0;
}