#include<iostream>
#include<utility>

template<typename T>
class SP
{
private:
    T* _data;
    int* _counter;

    void exchange(SP& rhs){
        if (_counter){
            --(*_counter);
        }
        _data = std::exchange(rhs._data, nullptr);
        _counter = std::exchange(rhs._counter, nullptr);
    }

    void copy(const SP& rhs){
        _data = rhs._data;
        _counter = rhs._counter;
        if (_counter){
            ++(*_counter);
        }
    }

public:
    // to prevent new operator failed
    explicit SP(T* data) 
    try
        : _data(data), _counter(new int(1)){}
    catch(...)
        {delete _data; throw;}
    
    ~SP()
    {
        if (_data){
            --(*_counter);
            if (*_counter == 0){
                delete _data;
                delete _counter;
                _data = nullptr;
                _counter = nullptr;
            }
        }
    }

    SP() : _data(nullptr), _counter(nullptr){}

    SP(const SP& copy) : _data(copy._data), _counter(copy._counter)
    {
        ++(*_counter);
    }

    // move constructor
    SP(SP&& rhs) noexcept {
        if (this != &rhs){
            this->exchange(rhs);
        }
    }
    
    // overload operator, it is not a deep copy only a pointer copy
    SP& operator=(const SP& rhs){
        if (this == &rhs || (rhs._counter == nullptr && _counter == nullptr)){
            return *this;
        }
        this->copy(rhs);
        return *this;
    }

    // move assignment
    SP& operator=(SP&& rhs) noexcept{
        if (this == &rhs || (rhs._counter == nullptr && _counter == nullptr)){
            return *this;
        }
        this->exchange(rhs);
        return *this;
    }

    SP& operator=(T* data){
        SP tmp(data);
        this->exchange(tmp);
        return *this;
    }

    T* operator->() const {return _data;};
    T& operator*() const {return *_data;};
    explicit operator bool() const {return _data;};

    T* get() const{return _data;};
    int getCounter() const{return *_counter;};
};


int main ()
{
    SP<int> t1(new int(10));
    //std::cout<<"Address: "<<t1.get()<<" val: "<<*t1.get()<<" counter "<<t1.getCounter()<<std::endl;
    SP<int> t2 = t1;
    std::cout<<"Address: "<<t2.get()<<" val: "<<*t2.get()<<" counter "<<t1.getCounter()<<std::endl;

    SP<int> t3(new int(20));
    t3 = t1;
    
    SP<int> t4(new int(50));
    t3 = std::move(t4);

    SP<int> t5(std::move(t3));
    SP<int> t8(new int(9));
    SP<int> t6;
    SP<int> t7;
    t6 = t7;
    t2 = t8;
    t1 = t8;

    SP<int> t9(nullptr); // nullptr and counter =1

    return 0;
}
