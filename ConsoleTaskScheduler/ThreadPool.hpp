#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>
#include <stdexcept>
#include <memory>
#include <type_traits>

class ThreadPool {
public:
    /// @brief Constructs a ThreadPool with the specified number of threads.
    explicit ThreadPool(size_t numThreads);

    /// @brief Destructs the ThreadPool, ensuring a graceful shutdown.
    ~ThreadPool();

    /// @brief Submit a task to the thread pool.
    /// @tparam F Callable type.
    /// @tparam Args Argument types.
    /// @param f The callable.
    /// @param args Arguments to pass to the callable.
    /// @return A std::future representing the task's result.
    template <class F, class... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

    /// @brief Shuts down the thread pool and joins all threads.
    void shutdown();

private:
    /// @brief Worker function that continuously processes tasks.
    void workerThread();

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex queueMutex_;
    std::condition_variable condition_;
    std::atomic<bool> stop_;
};

// Template function implementation
template <class F, class... Args>
auto ThreadPool::submit(F&& f, Args&&... args)
-> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    // Wrap the function and its arguments into a packaged_task.
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    std::future<return_type> res = task->get_future();

    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        if (stop_) {
            throw std::runtime_error("ThreadPool is stopped; cannot submit new tasks.");
        }
        tasks_.emplace([task]() { (*task)(); });
    }
    condition_.notify_one();
    return res;
}

#endif // THREADPOOL_HPP
