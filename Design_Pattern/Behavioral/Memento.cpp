#include <string>
#include <iostream>
#include <vector>

class Memento
{
    public:
        virtual ~Memento () {}
        virtual std::string GetName() const = 0;
        virtual std::string state() const = 0;
};

class ConcreteMemento : public Memento
{
    private:
        std::string state_;
        std::string date_;

    public:
        ConcreteMemento() = delete;
        explicit ConcreteMemento(std::string state) : state_(state) {};

        std::string state () const override
        {
            return state_;
        }

        std::string GetName() const override
        {
            return "( " + state_ + " )";
        }
};
class Originator {
    private:
        std::string state_;

    public:
        Originator(std::string state) : state_(state) 
        {
            std::cout << "Originator: My initial state is: " << state_ << "\n";
        }

        void UpdatState(std::string newstate) 
        {
            std::cout << "Originator: I'm doing something important.\n";
            state_ = newstate;
            std::cout << "Originator: and my state has updated to: " << state_ << "\n";
        }

        Memento *Save() 
        {
            return new ConcreteMemento(state_);
        }
        void Restore(Memento *memento) {
            state_ = memento->state();
            std::cout << "Originator: My state has backed to: " << state_ << "\n";
        }
};

class CareTaker
{
    private: 
        std::vector<Memento * > mementos_;

        Originator * originator_;
    public:
        CareTaker(Originator * originator) : originator_(originator) {}

        ~CareTaker() 
        {
            for (auto& m : mementos_) 
            {
                delete m;
            }
        }

        void BackUp() 
        {
            std::cout<<"\nCareTaker: Saving state \n"<<std::endl;
            mementos_.push_back(originator_ -> Save());
        }

        void Undo()
        {
            if (mementos_.size() == 0) 
            {
                return;
            }
            Memento * memento = mementos_.back();
            mementos_.pop_back();
            std::cout<<"Caretaker: Restoring state back to " << memento -> GetName() << std::endl;
            
            try
            {
                originator_->Restore(memento);
            } catch(...)
            {
                Undo();
            }
        }

        void ShowHistory() const
        {
            std::cout<<"CareTaker: show history \n"<<std::endl;
            for (const auto& m : mementos_)
            {
                std::cout<<m->GetName()<<std::endl;
            }
        }
};

void Client() 
{
    Originator * o = new Originator("State A");
    CareTaker * c = new CareTaker(o);
    c -> BackUp();
    o -> UpdatState("State B");
    c -> BackUp();
    o -> UpdatState("State C");
    c -> BackUp();

    c -> ShowHistory();

    std::cout<<"Roll back"<<std::endl;
    c -> Undo();
    std::cout<<"Roll back again"<<std::endl;
    c -> Undo();

    c -> ShowHistory();

    delete o;
    delete c;
}


int main() 
{
    Client();
    return 0;
}