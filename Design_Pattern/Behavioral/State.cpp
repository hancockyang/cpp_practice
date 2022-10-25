#include<iostream>
#include<string>
#include<memory>

class Context;

class IState
{
    public:
        virtual ~IState() = default;
        virtual void NextState(Context * context) const = 0;
        virtual const std::string GetName() const = 0;
};

class Context
{
    public:

        Context (std::unique_ptr<IState>&& state) : m_state(std::move(state)) {};
        

        void GetState() const 
        {
           std::cout<< m_state -> GetName();
        }
        void SetState(std::unique_ptr<IState> && state)
        {
            m_state = std::move(state);
        }
        void Request() 
        {
            m_state -> NextState(this);
        }

    private:
        std::unique_ptr<IState>  m_state;
};

class StateA;
class StateB;
class StateC;
class StateD;

class StateA : public IState
{
    public:
        StateA() = default;

        void NextState(Context * context) const override;

        const std::string GetName() const override
        {
            return "Current State is A\n";
        }

};

class StateB : public IState
{
    public:
        StateB() = default;

        void NextState(Context * context) const override;
        const std::string GetName() const override
        {
            return "Current State is B\n";
        }
};

class StateC : public IState
{
    public:
        StateC() = default;

        void NextState(Context * context) const override;
        const std::string GetName() const override
        {
            return "Current State is C\n";
        }

};

class StateD : public IState
{
    public:
        StateD() = default;

        void NextState(Context * context) const override;
        const std::string GetName() const override
        {
            return "Current State is D\n";
        }

};

void StateD :: NextState(Context * context) const
{
    std::cout<<"Do some business logic for state - D"<<std::endl;
    std::cout<<"Setting to next state..."<<std::endl;
    context -> SetState(std::make_unique<StateA>());
}

void StateA :: NextState(Context * context) const
{
    std::cout<<"Do some business logic for state - A"<<std::endl;
    std::cout<<"Setting to next state..."<<std::endl;
    context -> SetState(std::make_unique<StateB>());
}

void StateB :: NextState(Context * context) const
{
    std::cout<<"Do some business logic for state - B"<<std::endl;
    std::cout<<"Setting to next state..."<<std::endl;
    context -> SetState(std::make_unique<StateC>());
}

void StateC :: NextState(Context * context) const
{
    std::cout<<"Do some business logic for state - C"<<std::endl;
    std::cout<<"Setting to next state..."<<std::endl;
    context -> SetState(std::make_unique<StateD>());
};



int main ()
{
    Context * c = new Context(std::make_unique<StateA>());
    c -> Request();
    c -> GetState();
    c -> Request();
    c -> Request();
    c -> GetState();
    c -> Request();
    c -> Request();
    c -> GetState();

    delete c;
    return 0;
};