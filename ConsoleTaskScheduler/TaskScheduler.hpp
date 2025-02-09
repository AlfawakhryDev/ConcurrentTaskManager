#ifndef TASKSCHEDULER_HPP
#define TASKSCHEDULER_HPP

#include "ThreadPool.hpp"
#include <functional>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

// Represents a scheduled task with an execution time.
struct ScheduledTask {
    std::chrono::steady_clock::time_point executeTime;
    std::function<void()> task;

    // Comparison operator: tasks with earlier executeTime have higher priority.
    bool operator>(const ScheduledTask& other) const {
        return executeTime > other.executeTime;
    }
};

class TaskScheduler {
public:
    /// @brief Constructs a TaskScheduler with an internal ThreadPool.
    /// @param numThreads Number of worker threads (default uses hardware concurrency).
    explicit TaskScheduler(size_t numThreads = std::thread::hardware_concurrency());

    /// @brief Destructs the TaskScheduler, ensuring graceful shutdown.
    ~TaskScheduler();

    /// @brief Schedule a task to be executed after a specified delay.
    /// @param task The callable task.
    /// @param delay Delay in milliseconds before execution.
    void schedule(const std::function<void()>& task, std::chrono::milliseconds delay);

    /// @brief Schedule a task to be executed at a specific time point.
    /// @param task The callable task.
    /// @param timePoint The time point at which to execute the task.
    void scheduleAt(const std::function<void()>& task, std::chrono::steady_clock::time_point timePoint);

    /// @brief Starts the scheduler's timer thread.
    void start();

    /// @brief Stops the scheduler and waits for all tasks to complete.
    void stop();

private:
    /// @brief The thread pool used to execute tasks.
    ThreadPool threadPool_;

    /// @brief Priority queue for scheduled tasks.
    std::priority_queue<ScheduledTask, std::vector<ScheduledTask>, std::greater<ScheduledTask>> taskQueue_;

    /// @brief Mutex to protect access to the task queue.
    std::mutex queueMutex_;

    /// @brief Condition variable to signal the timer thread.
    std::condition_variable queueCondition_;

    /// @brief Timer thread that dispatches tasks.
    std::thread timerThread_;

    /// @brief Flag to signal the scheduler to stop.
    std::atomic<bool> stopFlag_;

    /// @brief Function run by the timer thread that dispatches tasks when due.
    void timerFunction();
};

#endif // TASKSCHEDULER_HPP
