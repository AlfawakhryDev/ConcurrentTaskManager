#include "TaskScheduler.hpp"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::cout << "Starting Task Scheduler demo...\n";

    // Create a TaskScheduler with 4 worker threads.
    TaskScheduler scheduler(4);
    scheduler.start();

    // Schedule tasks with varying delays.
    scheduler.schedule([] {
        std::cout << "Task 1 executed after 1 second.\n";
        }, std::chrono::milliseconds(1000));

    scheduler.schedule([] {
        std::cout << "Task 2 executed after 2 seconds.\n";
        }, std::chrono::milliseconds(2000));

    scheduler.schedule([] {
        std::cout << "Task 3 executed after 3 seconds.\n";
        }, std::chrono::milliseconds(3000));

    // Wait long enough for all tasks to be executed.
    std::this_thread::sleep_for(std::chrono::seconds(4));

    scheduler.stop();
    std::cout << "Task Scheduler demo finished.\n";
    return 0;
}
