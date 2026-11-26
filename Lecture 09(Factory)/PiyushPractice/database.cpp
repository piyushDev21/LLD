#include <iostream>
using namespace std;

class Database{
    public:
    virtual void connect()=0;
    virtual ~Database(){};
};

class MySqlDb:public Database{
    void connect() override{
        cout<<"Connected to SQL"<<endl;
    }
};

class MongoDB:public Database{
    void connect() override{
        cout<<"Connected to MongoDB"<<endl;
    }
};

class PostgreSQLDb:public Database{
    void connect() override{
        cout<<"Connected to PostgreSQL"<<endl;
    }
};

class DataBaseFactory{
    public:
    Database*createDatabase(string &type){
        if(type=="MySql"){
            return new MySqlDb();
        }
        else if(type=="PostgreSQL"){
            return new PostgreSQLDb();
        }
        else if(type=="MongoDb"){
            return new MongoDB();
        }
        else{
            return nullptr;
        }
    }
};

int main(){
    string type="MySql";
    DataBaseFactory* factory=new DataBaseFactory();

    Database*database=factory->createDatabase(type);

    database->connect();

    delete factory;
    delete database;

    return 0;
}