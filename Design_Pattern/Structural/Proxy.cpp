#include <iostream>

class Subject 
{
    public:
        virtual void Request () const = 0;
};

class RealSubject : public Subject 
{
    public:
    // real work is done here;

        void Request () const override
        {
            std::cout << "RealSubject:: handling request." << std::endl;
        }
};

class Proxy : public Subject
{
    private:
        Subject *real_subject_;

        bool CheckAccess () const
        {
            std::cout<<"Proxy: Checking access prior to file a real request"<<std::endl;
            return true;
        }

        void LogAccess () const 
        {
            std::cout << "Proxy: Logging the time of request" <<std::endl;
        }

    public:
        Proxy (RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject))
        {

        }

        ~Proxy () 
        {
            delete real_subject_;
        }

        void Request () const override
        {
            if (CheckAccess()) 
            {
                real_subject_ -> Request();
                LogAccess();
            }
        }

};

void ClientCode (const Subject& subject) 
{
    subject.Request();
}

int main()
{
    std::cout<<"Run with real subject"<<std::endl;
    RealSubject *realsubject = new RealSubject();
    ClientCode(*realsubject);

    std::cout<<"Run with proxy"<<std::endl;
    Proxy *proxy = new Proxy(realsubject);
    ClientCode(*proxy);

    delete realsubject;
    delete proxy;

    return 0;

};