#include<iostream>
#include<string>
#include<vector>
#include<memory>


class Element;
class CPU;
class GPU;
class MontherBoard;


//IVistor

class IVistor
{
    public:
        virtual ~IVistor() = default;
        virtual void visitCPU(const CPU* ) const = 0;
        virtual void visitGPU(const GPU* ) const = 0;
        virtual void visitMontherBoard(const MontherBoard* ) const = 0;
};

class IElement
{
    public:
        virtual ~IElement() = default;
        virtual void runTest(IVistor* ) const = 0;
        virtual const std::string getName() const = 0;
};

class  CPU: public IElement 
{
    public:
        CPU() = delete;
        explicit CPU(std::string name_) : name (name_){};
        void runTest(IVistor * IV_ptr) const override
        {
            IV_ptr -> visitCPU(this);
        }

        const std::string getName() const override
        {
            return name;
        }
    private:
        std::string name;
};

class  GPU: public IElement 
{
    public:
        GPU() = delete;
        explicit GPU(std::string name_) : name (name_){};
        void runTest(IVistor * IV_ptr) const override
        {
            IV_ptr -> visitGPU(this);
        }
        const std::string getName() const override
        {
            return name;
        }
    private:
        std::string name;
};

class  MontherBoard: public IElement 
{
    public:
        MontherBoard() = delete;
        explicit MontherBoard(std::string name_) : name (name_){};
        void runTest(IVistor * IV_ptr) const override
        {
            IV_ptr -> visitMontherBoard(this);
        }
        const std::string getName() const override
        {
            return name;
        }
    private:
        std::string name;
};

class CircuitDetector : public IVistor
{
    public:
        CircuitDetector() = delete;
        explicit CircuitDetector(std::string name_) : name(name_) {};
        
        void  visitCPU(const CPU* cpu_ptr)  const override
        {
            std::cout<<"CircuitDector: " << name << " tested CPU" <<" ( "<<cpu_ptr->getName() <<" )"<<std::endl;
        }

        void  visitGPU(const GPU* gpu_ptr) const override
        {
            std::cout<<"CircuitDector: " << name << " tested GPU" <<" ( "<<gpu_ptr->getName() <<" )"<<std::endl;
        }

        void  visitMontherBoard(const MontherBoard* mb_ptr)  const override
        {
            std::cout<<"CircuitDector: " << name << " tested MontherBoard" <<" ( "<<mb_ptr->getName() <<" )"<<std::endl;
        }
    private:
        std::string name;
};

class FunctionDetector : public IVistor
{
    public:
        FunctionDetector() = delete;
        explicit FunctionDetector(std::string name_) : name(name_) {};
        
        void  visitCPU(const CPU* cpu_ptr) const override
        {
            std::cout<<"FuntionDector: " << name << " tested CPU" <<" ( "<<cpu_ptr->getName() <<" )"<<std::endl;
        }

        void  visitGPU(const GPU* gpu_ptr) const override
        {
            std::cout<<"FuntionDector: " << name << " tested GPU" <<" ( "<<gpu_ptr->getName() <<" )"<<std::endl;
        }

        void  visitMontherBoard(const MontherBoard* mb_ptr)  const override
        {
            std::cout<<"FunctionDector: " << name << " tested MontherBoard" <<" ( "<<mb_ptr->getName() <<" )"<<std::endl;
        }
    private:
        std::string name;
};


class Computer
{
    public:
        Computer() =  delete;
        Computer(IElement* cpu_,
                 IElement* gpu_,
                 IElement* mb_): cpu(cpu_), gpu(gpu_), mb(mb_){};
        void runTests(IVistor* v_ptr)
        {
            cpu -> runTest(v_ptr);
            gpu -> runTest(v_ptr);
            mb -> runTest(v_ptr);
        }

    private:
        IElement * cpu;
        IElement * gpu;
        IElement * mb;

};


int main()
{
    IElement * cpu = new CPU("Intel");
    IElement * gpu = new GPU("NV");
    IElement * mb = new MontherBoard("XXX");

    Computer * pc = new Computer(cpu, gpu, mb);

    IVistor * Jeff = new CircuitDetector("Jeff");
    IVistor * Dan = new FunctionDetector("Dan");

    pc -> runTests(Jeff);
    pc -> runTests(Dan);

    delete Jeff;
    delete Dan;
    delete pc;
    delete cpu;
    delete gpu;
    delete mb;

    return 0;
}