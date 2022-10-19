#include <string>
#include <iostream>
#include <memory>

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
        std::shared_ptr<Component> component;
    
    public:
        Decorator (std::shared_ptr<Component> _component) : component {_component} 
        {
        }

        std::string printOut () const override 
        {
            return component -> printOut();
        }
};

class Email : public Decorator
{
    public:
        Email (std::shared_ptr<Component> _component) : Decorator {_component} {};

        std::string printOut () const override
        {
            return "Send Email, " + component -> printOut();
        }

};

class SMS : public Decorator
{
    public:
        SMS (std::shared_ptr<Component> _component) : Decorator {_component} {};

        std::string printOut () const override
        {
            return "Send SMS, " + component -> printOut();
        }

};

class Whatsapp : public Decorator
{
    public:
        Whatsapp (std::shared_ptr<Component> _component) : Decorator {_component} {};

        std::string printOut () const override
        {
            return "Send Whatsapp, " + component -> printOut();
        }
};




int main() 
{
    std::shared_ptr<Component> messge = std::make_shared<SimpleComponent>();

    std::shared_ptr<Component> email = std::make_shared<Email>(messge);
    std::shared_ptr<Component> whatsapp = std::make_shared<Whatsapp>(email);
    std::shared_ptr<Component>sms = std::make_shared<SMS>(&whatsapp);

    std::string ss = sms -> printOut();
    std::cout<<ss<<std::endl;

    return 0;
}
