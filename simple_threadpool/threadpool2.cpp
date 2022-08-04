
#include <vector>
#include <thread>
#include <queue>
#include <deque>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <boost/circular_buffer.hpp>
#include <iostream>
#include <future>
#include <memory>

class Task {


public:
    Task() = default;
    template <class Fun>
    Task(Fun&& f) : ptr_{new Wrapper{std::move(f)}} {}

    void operator() () {ptr_ -> call();}

private:
    class Wrapper_base {
    public:
        virtual void call() = 0;
        virtual ~Wrapper_base() = default;

    };

    template<class Fun>
    class Wrapper : public Wrapper_base {
    public:
        explicit Wrapper(Fun&& f) :_f{std::move(f)} {}
        virtual void call() override { _f(); }
    private:
        Fun _f;
    };

    std::unique_ptr<Wrapper_base> ptr_;

};

class Threadpool {
public:
    explicit Threadpool (std::size_t);
    ~Threadpool ();

    void start(std::size_t);


    void stop();

    template <class Fun, class Ret = std::invoke_result_t<Fun>>
    std::future<Ret> submit(Fun );

private:
    void worker ();
    std::vector<std::thread> threads;
    boost::circular_buffer<Task> taskQueue;
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

void Threadpool::worker () {
    while (true) {
        Task t;
        {
            // one job is finished, waiting for next job
            std::unique_lock lk {mtx};
            notifyWorker.wait(lk, [this] () {return !isRunning || !taskQueue.empty();});

            assert(!isRunning || !taskQueue.empty());

            if (taskQueue.empty()) return;

            t = std::move(taskQueue.front());
            taskQueue.pop_front();
            notifyCusotmer.notify_one();
        }

        t();
    }

}

//template <class Fun, typename... Args>
template <class Fun, class Ret = std::invoke_result_t<Fun>>
std::future<Ret> Threadpool::submit(Fun f) {
    /**
     * @brief 
     * 
     * lock threapool until its got notified or the taskqueue is not full
     */
    std::packaged_task<Ret()> pt{std::move(f)};
    auto ret = pt.get_future();

    Task t {std::move(pt)};

    {
        std::unique_lock lk{mtx}; // lock threadpool
        notifyCusotmer.wait(lk, [this] () { return !isRunning || !taskQueue.full();});

        assert(!isRunning || !taskQueue.full());

        if (!isRunning) {
            return {};
        }
        taskQueue.push_back(std::move(t));
        notifyWorker.notify_one();

    }



    return ret;

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

    std::vector<std::future<int>> rets;

    for (int i = 0; i < 100; ++i) {
        auto ret = pool.submit(std::move([i](){return i;}));
        rets.push_back(std::move(ret));
    }
    pool.stop();

    for (auto& ret : rets) {
        std::cout<< ret.get() << " "<< std::endl;
    }

    
    return 0;
}