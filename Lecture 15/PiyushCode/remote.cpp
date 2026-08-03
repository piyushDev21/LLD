#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Light
{
public:
    void on()
    {
        cout << "Light is turn on" << endl;
    }
    void off()
    {
        cout << "Light is turned off" << endl;
    }
};

class Fan
{
public:
    void on()
    {
        cout << "Fan is turn on" << endl;
    }
    void off()
    {
        cout << "Fan is turned off" << endl;
    }
};

class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

class LightCommand : public Command
{
private:
    Light *light;

public:
    LightCommand(Light *light)
    {
        this->light = light;
    }

    void execute() override
    { // overide tells to check the execute is taken from the parent if fails Like by mistake I write "ExCute" it will through error That no function like that defined in the parent
        light->on();
    }

    void undo() override
    {
        light->off();
    }
};

class FanCommand : public Command
{
private:
    Fan *fan;

public:
    FanCommand(Fan *fan)
    {
        this->fan = fan;
    }

    void execute()//will work correctly too but if written wrong compiler will treat is as a new functio defined in the child class.
    {
        fan->on();
    }

    void undo()
    {
        fan->off();
    }
};

class RemoteController
{
private:
    static const int numButtons = 4;
    Command *buttons[numButtons];
    bool buttonPressed[numButtons];

public:
    RemoteController()
    {
        for (int i = 0; i < 4; i++)
        {
            buttons[i] = nullptr;
            buttonPressed[i] = false;
        }
    }

    void setCommand(int idx, Command *cmd)
    {
        if (idx >= 0 && idx < numButtons)
        {
            if (buttons[idx] != nullptr)
            {
                delete buttons[idx];
            }
            buttons[idx] = cmd;
            buttonPressed[idx] = false;
        }
    }

    void pressButton(const int &idx)
    {
        if (idx >= 0 && idx < numButtons && buttons[idx] != nullptr)
        {
            if (buttonPressed[idx] == false)
            {
                buttons[idx]->execute();
                buttonPressed[idx] = true;
            }
            else
            {
                buttons[idx]->undo();
                buttonPressed[idx] = false;
            }
        }
        else
        {
            cout << "No function assigned to the button " << idx << endl;
        }
    }

    ~RemoteController()
    {
        for (int i = 0; i < numButtons; i++)
        {
            if (buttons[i] != nullptr)
            {
                delete buttons[i];
            }
        }
    }
};

int main()
{

    Light *livingRoomLight = new Light();
    Fan *ceilingFan = new Fan();

    RemoteController *remote = new RemoteController();

    remote->setCommand(0, new LightCommand(livingRoomLight));
    remote->setCommand(1, new FanCommand(ceilingFan));

    cout << "---------Testing Living Room Light--------" << endl;
    remote->pressButton(0);
    remote->pressButton(0);

    cout << "---------Testing Ceiling Fan--------" << endl;
    remote->pressButton(1);
    remote->pressButton(1);

    cout << "--------------Test unassigned button----------" << endl;
    remote->pressButton(3);

    delete remote;
    delete livingRoomLight;
    delete ceilingFan;

    return 0;
};
