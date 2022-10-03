#include <string>
#include <iostream>

class Component 
{
    public:
        virtual ~Component() {}
        virtual std::string printOut() const = 0;
};

class SimpleComponent : public Component 
{
    public:
        std::string printOut () const override 
        {
            return " This is message... ";
        }

};

class Decorator : public Component 
{
    protected:
        Component *component;
    
    public:
        Decorator (Component * _component) : component {_component} 
        {
        }

        std::string printOut () const override 
        {
            return this -> component -> printOut();
        }
};

class Email : public Decorator
{
    public:
        Email (Component* _component) : Decorator {_component} {};

        std::string printOut () const override
        {
            return "Send Email, " + component -> printOut();
        }

};

class SMS : public Decorator
{
    public:
        SMS (Component* _component) : Decorator {_component} {};

        std::string printOut () const override
        {
            return "Send SMS, " + component -> printOut();
        }

};

class Whatsapp : public Decorator
{
    public:
        Whatsapp (Component* _component) : Decorator {_component} {};

        std::string printOut () const override
        {
            return "Send Whatsapp, " + component -> printOut();
        }
};




int main() 
{
    Component *messge = new SimpleComponent;

    Component *email = new Email(messge);
    Component *whatsapp = new Whatsapp(email);
    Component *sms = new SMS(whatsapp);

    std::string ss = sms -> printOut();
    std::cout<<ss<<std::endl;
    delete sms;
    delete whatsapp;
    delete email;
    delete messge;

    return 0;
}
