
#include<iostream>
#include<utility>
template<typename T>
class UP{
    T* _data;
    void exchange(UP& move){
        this->_data = std::exchange(move._data, nullptr);
    }
public:
    UP () : _data(nullptr){};
    explicit UP (T* data) : _data(data){};
    ~UP() { 
        delete _data;
        _data = nullptr;
    }
    // no copy constructor and copy assignment
    UP (const UP& copy) = delete;
    UP& operator=(const UP& copy) = delete;

    UP& operator=(T* data){
        this->_data = data;
        return *this;
    }

    //move construcotr and move assignment
    UP (UP&& move) noexcept : _data(std::exchange(move._data, nullptr))  {};

    UP& operator=(UP&& move) noexcept {
        this->exchange(move);
        return *this;
    }

    T* operator->(){
        return _data;
    }
    T& operator*(){
        return *_data;
    }
    //access to data
    T* get()                 const {return _data;}
    explicit operator bool() const {return _data;}

    //release
    T* release(){
        _data = nullptr;
        return this;
    }
};


int main(){
    UP<int> up1(new int(10));
    UP<int> up2;
    up2 = new int(0);
    std::cout<<"address: "<<up1.get()<<std::endl;
    up1 = std::move(up2);
    return 0;
}