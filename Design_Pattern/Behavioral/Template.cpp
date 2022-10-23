#include<iostream>
#include<memory>

class ITemplate
{
    public:
        void runBusinessLogic() 
        {
            BaseMethod1();
            BaseMethod2();
            Customized1();
            Customized2();
            Optional1();
            Optional2();
        }
    private:
        void BaseMethod1() const 
        {
            std::cout<<"Run base method 1"<<std::endl;
        }
        void BaseMethod2() const 
        {
            std::cout<<"Run base method 2"<<std::endl;
        }

        virtual void Customized1 () const = 0;
        virtual void Customized2 () const = 0;

        virtual void Optional1 () const
        {
            std::cout<<"Run default optional method 1"<<std::endl;
        };
        virtual void Optional2 () const
        {
            std::cout<<"Run default optional method 2"<<std::endl;
        }
};


class TemplateA : public ITemplate
{
    private:
        void Customized1 () const override
        {
            std::cout<<"Run Template A's customized method 1"<<std::endl;
        }
        void Customized2 () const override
        {
            std::cout<<"Run Template A's customized method 2"<<std::endl;
        }
};

class TemplateB : public ITemplate
{
    private:
        void Customized1 () const override
        {
            std::cout<<"Run Template B's customized method 1"<<std::endl;
        }
        void Customized2 () const override
        {
            std::cout<<"Run Template B's customized method 2"<<std::endl;
        }
        void Optional1 () const override
        {
            std::cout<<"Run Template B's optional method 1"<<std::endl;
        }
};

void ClientCode(std::unique_ptr<ITemplate> && ptr) 
{
    ptr -> runBusinessLogic();
}

int main()
{
    std::unique_ptr<ITemplate> ptr1 = std::make_unique<TemplateA>();
    std::unique_ptr<ITemplate> ptr2 = std::make_unique<TemplateB>();
    ClientCode(std::move(ptr1));
    ClientCode(std::move(ptr2));
    return 0;
}