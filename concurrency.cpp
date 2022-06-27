#include<thread>
#include<iostream>
#include<mutex>


int main(){
    int result{0};
    std::mutex mtx;
    mtx.lock();// lock by thread A
    std::thread threadB = std::thread(
        [&](){
            // now lock by thread B
            mtx.lock();
            std::cout<<"Hello from thread B"<<std::endl;
            result = 42;
            mtx.unlock(); // release by thread B
        }
    );
    std::cout<<"Hello from thread A"<<std::endl;
    mtx.unlock(); // release by thread A
    threadB.join();
    std::cout<<"Results = "<<result<<std::endl;
    std::cout<<"Hello again from thread A"<<std::endl;
    return 0;
}