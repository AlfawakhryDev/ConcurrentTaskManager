#include "TaskScheduler.hpp"
#include <iostream>

TaskScheduler::TaskScheduler(size_t numThreads)
    : threadPool_(numThreads), stopFlag_(false) {
}

TaskScheduler::~TaskScheduler() {
    stop();
}

void TaskScheduler::start() {
    stopFlag_ = false;
    timerThread_ = std::thread(&TaskScheduler::timerFunction, this);
}

void TaskScheduler::stop() {
    stopFlag_ = true;
    queueCondition_.notify_all();
    if (timerThread_.joinable()) {
        timerThread_.join();
    }
    threadPool_.shutdown();
}

void TaskScheduler::schedule(const std::function<void()>& task, std::chrono::milliseconds delay) {
    auto timePoint = std::chrono::steady_clock::now() + delay;
    scheduleAt(task, timePoint);
}

void TaskScheduler::scheduleAt(const std::function<void()>& task, std::chrono::steady_clock::time_point timePoint) {
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        taskQueue_.push(ScheduledTask{ timePoint, task });
    }
    queueCondition_.notify_one();
}

void TaskScheduler::timerFunction() {
    while (!stopFlag_) {
        std::unique_lock<std::mutex> lock(queueMutex_);
        if (taskQueue_.empty()) {
            // Wait until a new task is scheduled or stopFlag is set.
            queueCondition_.wait(lock, [this] { return stopFlag_ || !taskQueue_.empty(); });
        }
        else {
            auto now = std::chrono::steady_clock::now();
            auto nextTaskTime = taskQueue_.top().executeTime;
            if (now >= nextTaskTime) {
                // Task is ready to execute.
                auto scheduledTask = taskQueue_.top();
                taskQueue_.pop();
                lock.unlock();
                // Submit the task to the thread pool.
                threadPool_.submit(scheduledTask.task);
            }
            else {
                // Wait until the next task is due or a new task is scheduled.
                queueCondition_.wait_until(lock, nextTaskTime, [this, nextTaskTime] {
                    return stopFlag_ || (!taskQueue_.empty() && taskQueue_.top().executeTime < nextTaskTime);
                    });
            }
        }
    }
}
