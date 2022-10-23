#include <memory>
#include <string>
#include <iostream>

class IStrategy
{
    public:
        virtual ~IStrategy() = default;
        virtual std::string doMethod() const = 0;
        virtual std::string getMethod() const = 0;
};

class Context
{
    private:
        std::unique_ptr<IStrategy> strategy;
    
    public:
        explicit Context(std::unique_ptr<IStrategy> &&ss = {}) : strategy{std::move(ss)} {};

        void set_strategy(std::unique_ptr<IStrategy> && ss) 
        {
            strategy = std::move(ss);
            std::cout<<"setting strategy to "<<strategy->getMethod()<<std::endl;
        }

        void doBusinessLogic() const
        {
            if (strategy) 
            {
                std::cout<<"Doing business logic ... "<<std::endl;
                std::cout<<strategy -> doMethod()<<std::endl;
            } 
            else
            {
                std::cout<<"No method setup yet"<<std::endl;
            }
        }

};

class StrategyA : public IStrategy
{
    public:
        std::string doMethod() const override
        {
            return "Using stragety A";
        }

        std::string getMethod() const override
        {
            return "Stragety A";
        }
};

class StrategyB  : public IStrategy
{
    public:
        std::string doMethod() const override
        {
            return "Using stragety B";
        }

        std::string getMethod() const override
        {
            return "Stragety B";
        }
};

void ClientCode ()
{
    std::unique_ptr<Context> c = std::make_unique<Context>(std::make_unique<StrategyA>());
    c -> doBusinessLogic();
    c -> set_strategy(std::make_unique<StrategyB>());
    c -> doBusinessLogic();
};

int main ()
{
    ClientCode();
    return 0;
}