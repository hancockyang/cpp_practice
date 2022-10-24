#include<iostream>
#include<string>
#include<vector>
#include<list>

class IObserver
{
    public:
        virtual ~IObserver() = default;
        virtual void Update(const std::string & msg) const  = 0;
};

class ISubject
{
    public:
        virtual ~ISubject() = default;
        virtual void registerObsvr(const IObserver * obsvr) = 0;
        virtual void removeObsvr(const IObserver * obsvr) = 0;
        virtual void notifyObsvrs(const std::string & msg) = 0;
};

class Subject : public ISubject
{
    public:
        virtual ~Subject() override
        {
            std::cout<<"Destruct a subject"<<std::endl;
        }

        void registerObsvr(const IObserver * obsvr) override
        {
            obsvrList.push_back(obsvr);
        }

        void removeObsvr(const IObserver * obsvr) override
        {
            obsvrList.remove(obsvr);
        }


        void notifyObsvrs(const std::string & msg) override
        {
            for(auto it = obsvrList.begin(); it != obsvrList.end(); it++)
            {
                (*it) -> Update(msg);
            }
        }


    private:
        std::list<const IObserver *> obsvrList;
};

class Observer : public IObserver
{
    public:
        Observer() = default;

        explicit Observer(ISubject * sub) : sub_(sub) 
        {
            sub_ -> registerObsvr(this);
            Observer::totalObsvrs++;
            num = Observer::totalObsvrs;
        }

        ~Observer() override
        {
            std::cout<<"Destruct an observer"<<std::endl;
        }

        void RemoveMe()
        {
            if (sub_)
            {
                sub_ -> removeObsvr(this);
                Observer::totalObsvrs--;
                num = -1;
            }
        }

        void Update(const std::string & msg) const override
        {
            std::cout<<"Recieved msg: " <<msg<<" , updating ... "<<std::endl;
            std::cout<<"Observer "<< num <<" do some business logic ... "<<std::endl;
        }

    private:
        ISubject * sub_;
        static int totalObsvrs;
        int num;
    
};

int Observer::totalObsvrs = 0;

int main()
{
    ISubject * s1 = new Subject();
    Observer * o1 = new Observer(s1);
    Observer * o2 = new Observer(s1);
    Observer * o3 = new Observer(s1);

    s1->notifyObsvrs("Ok");

    o2 ->RemoveMe();

    s1->notifyObsvrs("Fine");

    delete s1;
    delete o1;
    delete o2;
    delete o3;
    
    return 0;
}