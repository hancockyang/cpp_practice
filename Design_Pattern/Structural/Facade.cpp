#include <iostream>

class SubsystemOne
{
    public:
        void m1() {std::cout<<"subsytem 1, method 1"<<std::endl;}
        void m2() {std::cout<<"subsytem 1, method 2"<<std::endl;}
};

class SubsystemTwo
{
    public:
        void m1() {std::cout<<"subsytem 2, method 1"<<std::endl;}
        void m2() {std::cout<<"subsytem 2, method 2"<<std::endl;}
};

class SubsystemThree
{
    public:
        void m1() {std::cout<<"subsytem 3, method 1"<<std::endl;}
        void m2() {std::cout<<"subsytem 3, method 2"<<std::endl;}
};

class Facade
{
    public:
        Facade () : pOne{new SubsystemOne()}, pTwo{new SubsystemTwo()}, pThree{new SubsystemThree()} {}

        void method ()
        {
            pOne -> m1();
            pOne -> m2();
            pTwo -> m1();
            pTwo -> m2();
            pThree -> m1();
            pThree -> m2();
        }

        ~Facade() {
            delete pOne;
            delete pTwo;
            delete pThree;
        }

    private:
        SubsystemOne *pOne;
        SubsystemTwo *pTwo;
        SubsystemThree *pThree;
};

void client (Facade* f)
{
    f -> method();

};

int main() 
{
    Facade *f = new Facade();
    client(f);
    delete f;
    return 0;
}