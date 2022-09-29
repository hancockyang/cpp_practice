#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;
class ExecuteInterface {
    public:
    // 1. Specify the new interface
        virtual ~ExecuteInterface(){}
        virtual void execute() = 0;
};

// 2. Design a "wrapper" or "adapter" class
template <class TYPE>
class ExecuteAdapter: public ExecuteInterface {
    //using fcptr = void(TYPE::*)();
    public:
        ExecuteAdapter(std::unique_ptr<TYPE> o, std::function<void(TYPE*)> m) :
            object(std::move(o)), method(std::move(m))

        {}

        ~ExecuteAdapter() 
        {
            
        }
        // 4. The adapter/wrapper "maps" the new to the legacy implementation
        void execute() 
        {  /* the new */
            //(object.get()->*method)();
            method(object.get());
        }
    private:
        std::unique_ptr<TYPE> object; // ptr-to-object attribute

        std::function<void(TYPE*)> method; /* the old */     // ptr-to-member-function attribute
};


// The old: three totally incompatible classes
// no common base class,
class Fea {
    public:
     // no hope of polymorphism
    Fea() {}
    ~Fea() 
    {
        std::cout << "Fea::dtor" << std::endl;
    }
    void doThis() 
    {
        std::cout << "Fea::doThis()" << std::endl;
    }
};

class Feye {
    public:~Feye() 
    {
        std::cout << "Feye::dtor" << std::endl;
    }
    void doThat() 
    {
        std::cout << "Feye::doThat()" << std::endl;
    }
};

class Pheau {
    public:
    ~Pheau() 
    {
        std::cout << "Pheau::dtor" << std::endl;
    }
    void doTheOther() 
    {
        std::cout << "Pheau::doTheOther()" << std::endl;
    }
};


/* the new is returned */
std::vector<std::unique_ptr<ExecuteInterface>> initialize() {


    std::vector<std::unique_ptr<ExecuteInterface>> array;

  /* the old is below */
    array.push_back(std::make_unique<ExecuteAdapter<Fea>>(std::make_unique<Fea>(), &Fea::doThis));
    array.push_back(std::make_unique<ExecuteAdapter<Feye>>(std::make_unique<Feye>(), &Feye::doThat));
    array.push_back(std::make_unique<ExecuteAdapter<Pheau>>(std::make_unique<Pheau>(), &Pheau::doTheOther));
    return array;
}

int main() {
    std::vector<std::unique_ptr<ExecuteInterface>> objects = initialize();
    // 3. Client uses the new (polymporphism)
    for (size_t i = 0; i < objects.size(); i++) 
    {
        objects[i]->execute();
    }

 
    return 0;
}