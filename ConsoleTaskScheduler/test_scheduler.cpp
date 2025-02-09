#include "TaskScheduler.hpp"
#include <iostream>
#include <atomic>
#include <cassert>
#include <chrono>
#include <thread>

int main() {
    std::cout << "Running TaskScheduler tests...\n";

    TaskScheduler scheduler(2);
    scheduler.start();

    std::atomic<int> counter{ 0 };

    // Schedule 5 tasks to increment the counter after 100 ms.
    for (int i = 0; i < 5; ++i) {
        scheduler.schedule([&counter] {
            counter.fetch_add(1);
            }, std::chrono::milliseconds(100));
    }

    // Wait enough time for all tasks to execute.
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    scheduler.stop();

    // Verify that the counter is exactly 5.
    assert(counter.load() == 5);
    std::cout << "All tests passed. Counter value: " << counter.load() << "\n";
    return 0;
}
