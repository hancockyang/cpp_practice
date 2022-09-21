#include <iostream>
#include <memory>
#include <string>

class Pizza{
public:
    void setDough(const std::string& dough){
        m_dough = dough;
    }
    void setSauce(const std::string& sauce){
        m_sauce = sauce;
    }
    void setTopping(const std::string& topping){
        m_topping = topping;
    }
    void open() const {
        std::cout<<"The Pizza have "<<
        m_dough<<" dough, "<<
        m_sauce<<" sauce, "<<
        m_topping<<" topping."<<
        std::endl;
    }
private:
    std::string m_dough;
    std::string m_sauce;
    std::string m_topping;
};

class PizzaBuilder{
public:
    virtual ~PizzaBuilder() = default;
    void createNewPizza(){
        m_pizza = std::make_unique<Pizza>();
    }
    Pizza* getPizza() const {
        return m_pizza.get();
    }
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
protected:
    std::unique_ptr<Pizza> m_pizza;
};

class HawaiianPizzaBuilder:public PizzaBuilder{
public:
    ~HawaiianPizzaBuilder() override = default;
    void buildDough() override {
        m_pizza->setDough("Hawaiian");
    }
    void buildSauce() override {
        m_pizza->setSauce("Hawaiian");
    }
    void buildTopping() override {
        m_pizza->setTopping("Hawaiian");
    }
};

class SpicyPizzaBuilder:public PizzaBuilder{
public:
    ~SpicyPizzaBuilder() override = default;
    void buildDough() override {
        m_pizza->setDough("Spicy");
    }
    void buildSauce() override {
        m_pizza->setSauce("Spicy");
    }
    void buildTopping() override {
        m_pizza->setTopping("Spicy");
    }
};

class CustomizePizzaBuilder:public PizzaBuilder{
public:
    CustomizePizzaBuilder (const std::string& _dough, const std::string& _source, const std::string& _topping) : 
            m_dough{_dough}, m_source{_source}, m_topping{_topping} {};
    ~CustomizePizzaBuilder() override = default;
    void buildDough() override {
        m_pizza->setDough(m_dough);
    }
    void buildSauce() override {
        m_pizza->setSauce(m_source);
    }
    void buildTopping() override {
        m_pizza->setTopping(m_topping);
    }
private:
    std::string m_dough, m_source, m_topping; 
};

class Cook{
public:
    void openPizza() const {
        m_pizzaBuilder->getPizza()->open();
    }
    void createPizza(std::unique_ptr<PizzaBuilder> pizzaBuilder){
        m_pizzaBuilder = std::move(pizzaBuilder);
        m_pizzaBuilder->createNewPizza();
        m_pizzaBuilder->buildDough();
        m_pizzaBuilder->buildSauce();
        m_pizzaBuilder->buildTopping();
    }
private:
    std::unique_ptr<PizzaBuilder> m_pizzaBuilder;
};

int main(){
    Cook cook{};
    std::unique_ptr<PizzaBuilder> p1 = std::make_unique<HawaiianPizzaBuilder>();
    cook.createPizza(std::move(p1));
    cook.openPizza();

    std::unique_ptr<PizzaBuilder> p2 = std::make_unique<SpicyPizzaBuilder>();
    cook.createPizza(std::move(p2));
    cook.openPizza();

    std::unique_ptr<PizzaBuilder> p3 = std::make_unique<CustomizePizzaBuilder>("A", "B", "C");
    cook.createPizza(std::move(p3));
    cook.openPizza();
    return 0;
}