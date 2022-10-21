#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

enum class PERSON_TYPE
{
    kUnknown,
    kLandlord,
    kTenant
};

class Component;


//Mediator interface
class Mediator
{
    public:
        virtual void registerComponent(Component*) = 0;
        
        virtual void notify(const Component*) const = 0;
};



class Component
{
    public:
        Component (Mediator* m, PERSON_TYPE p) : mediator(m), person_type_(p) {};

        virtual void answer() const = 0;
        virtual void ask() const = 0;

        Mediator* getMediator () const
        {
            return mediator;
        }

        PERSON_TYPE getPersonType () const
        {
            return person_type_;
        }

    private:
        Mediator *mediator;
        PERSON_TYPE person_type_;
};

class Landlord : public Component
{
    public:
        Landlord() = delete;
        Landlord (Mediator* m, PERSON_TYPE p, std::string name_, int price_, std::string address_, std::string phone_)
        : Component(m, p), name(name_), address(address_), phone(phone_), price(price_){};

        void answer() const override
        {
            printf("Landlord Name: %s, Rent: %i, Address: %s, Phone Number: %s\n", name.c_str(), price, address.c_str(), phone.c_str());
        }

        void ask() const override
        {
            printf("Landlord %s checks tenants' info\n", name.c_str());
            getMediator() -> notify(this);
        }

    private:
        std::string name, address, phone;
        int price;
};


class Tenant : public Component
{
    public:
        Tenant() = delete;
        Tenant (Mediator* m, PERSON_TYPE p, std::string name_, std::string phone_)
        : Component(m, p), name(name_), phone(phone_){};

        void answer() const override
        {
            printf("Tenant Name: %s, Phone Number: %s\n", name.c_str(), phone.c_str());
        }

        void ask() const override
        {
            printf("Tenant %s checks landlord' info\n", name.c_str());
            getMediator() -> notify(this);
        }

    private:
        std::string name, phone;

};

class Agent : public Mediator
{
    public:
        virtual void registerComponent (Component* c) override
        {
            switch (c -> getPersonType())
            {
            case PERSON_TYPE::kLandlord:
                Landlord_list.push_back(reinterpret_cast<Landlord*>(c));
                break;

            case PERSON_TYPE::kTenant:
                Tenant_list.push_back(reinterpret_cast<Tenant*>(c));
                break;
            default:
                printf("Wrong person type");
                break;
            }
        }

        virtual void notify(const Component* c) const override
        {
            switch (c -> getPersonType())
            {
            case PERSON_TYPE::kLandlord:
                for (int i = 0; i < Tenant_list.size(); ++i) 
                {
                    Tenant_list[i] -> answer();
                }
                break;
            case PERSON_TYPE::kTenant:
                break;
            default:
                break;
            }
        }
    private:
        std::vector<Landlord*> Landlord_list;
        std::vector<Tenant*> Tenant_list;
};


int main() 
{
    //client
    //agent
    Mediator *agent = new Agent();
    //Landlord
    Component *l1 = new Landlord(agent, PERSON_TYPE::kLandlord, "Jack", 11,"AA", "123");
    Component *l2 = new Landlord(agent, PERSON_TYPE::kLandlord, "Ann", 12,"BA", "13");
    Component *l3 = new Landlord(agent, PERSON_TYPE::kLandlord, "Wei", 14,"BB", "123");


    //Tenant
    Component *t1 = new Tenant(agent, PERSON_TYPE::kTenant, "Foo", "213");
    Component *t2 = new Tenant(agent, PERSON_TYPE::kTenant, "Bar", "231");

    agent -> registerComponent(l1);
    agent -> registerComponent(l2);
    agent -> registerComponent(l3);

    agent -> registerComponent(t1);
    agent -> registerComponent(t2);

    l1 -> ask();
    l2 -> ask();

    return 0;
}