#include <vector>
#include <thread>
#include <queue>
#include <deque>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <boost/circular_buffer.hpp>
#include <iostream>

using task = std::function<void()>;
class Threadpool {
public:
    explicit Threadpool (std::size_t);
    ~Threadpool ();

    void start(std::size_t);


    void stop();

    template <class Fun>
    void submit(Fun);

private:
    void worker () {
        while (true) {
            task t;
            {
                // one job is finished, waiting for next job
                std::unique_lock lk {mtx};
                notifyWorker.wait(lk, [this] () {return !isRunning || !taskQueue.empty();});

                assert(!isRunning || !taskQueue.empty());


                t = std::move(taskQueue.front());
                taskQueue.pop_front();
                notifyCusotmer.notify_one();
            }

            t();
            if (!isRunning && taskQueue.empty()) {
                return;
            }
        }

    }
    std::vector<std::thread> threads;
    boost::circular_buffer<task> taskQueue;
    std::mutex mtx;
    std::condition_variable notifyCusotmer, notifyWorker;
    bool isRunning;
};

Threadpool::Threadpool(std::size_t n) : isRunning (false), taskQueue {n} {};
Threadpool::~Threadpool() {stop();};

void Threadpool::start (std::size_t n) {
    if (isRunning) {
        return;
    }
    isRunning = true;
    threads.reserve(n);

    while (n--) {
        threads.emplace_back(&Threadpool::worker, this);
    }
}

//template <class Fun, typename... Args>
template <class Fun>
void Threadpool::submit(Fun f) {
    /**
     * @brief 
     * 
     * lock threapool until its got notified or the taskqueue is not full
     */
    std::unique_lock lk{mtx}; // lock threadpool
    notifyCusotmer.wait(lk, [this] () { return !isRunning || !taskQueue.full();});

    assert(!isRunning || !taskQueue.full());

    if (!isRunning) {
        return;
    }

    taskQueue.push_back(std::move(f));

    notifyWorker.notify_one();

}


void Threadpool::stop() {
    
    if (!isRunning) {
        return;
    }

    {
        std::lock_guard lk {mtx};
        isRunning = false;
        notifyCusotmer.notify_all();
        notifyWorker.notify_all();

    }


    for(auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }
}

//template <class Fun, typename... Args>
//Fun print(Args... a) {
//    std::cout<< Fun << std::endl; 
//    return a;
//}
int main() {
    Threadpool pool{10};

    pool.start(3);

//    std::mutex mtx;
//    mtx.lock();// lock by thread A
    std::thread::id main_thread = std::this_thread::get_id();
    for (int i = 0; i < 100; ++i) {

        pool.submit (
             [i]() {std::cout<< i << " "<< std::this_thread::get_id() << "\n" << std::endl;}
        );
       
    }

//    mtx.unlock();

    return 0;
}