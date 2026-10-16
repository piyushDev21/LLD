#include <iostream>
#include <string>
#include <vector>
using namespace std;

class IObserver{
    public:
    virtual void update(string const& video)=0;
    virtual ~IObserver(){};
};

class Subscriber:public IObserver{
    private:
    string name;

    public:
    Subscriber(string const &name){
        this->name=name;
    }

    void update(string const & video)override{
        cout<<"New video has been uploaded: "<<video<<endl;
    };
};

class Channel{
    private:
    string name;
    vector<IObserver*>subscribers;
    vector<string>videos;

    public:

    Channel(string const& name){
        this->name=name;
    };
    
    void subscribe(IObserver* subscriber){
        bool userFound=false;
        for(int i=0;i<subscribers.size();i++){
            if(subscribers[i]==subscriber){
                userFound=true;
                break;
            }
        }
        if(!userFound)subscribers.push_back(subscriber);
    };

    void unSubscribe(IObserver* subscriber){
        for(int i=0;i<subscribers.size();i++){
            if(subscribers[i]==subscriber){
                subscribers.erase(subscribers.begin() + i);              
                break;
            }
        }
    };

    void notify(string const& video){
        for(int i=0;i<subscribers.size();i++){
            subscribers[i]->update(video);
        };
    }

    void upload(string const & video){
        videos.push_back(video);
        notify(video);
    };
};

int main(){
    Subscriber* subscriber=new Subscriber("Piyush");
    Channel* bbKiVines=new Channel("BB ki Vines");
    bbKiVines->subscribe(subscriber);
    bbKiVines->upload("DARRU WITH DAD");

    delete bbKiVines;
    delete subscriber;
};

