# Concurrent Task Scheduler - Single File Visual Studio C++ Project

## Overview
This project implements a **Concurrent Task Scheduler** in modern C++ (C++17) using advanced design principles. It allows you to schedule tasks to be executed concurrently after a specified delay or at a designated time. The scheduler uses a custom thread pool to efficiently manage multiple worker threads, and demonstrates robust design practices including RAII, exception safety, and clean code architecture.

This project is packaged as a single file to simplify setup and deployment in Microsoft Visual Studio.

## Features
- **Concurrent Task Scheduling:** Schedule tasks to run after a delay or at a specific time.
- **Thread Pool:** A lightweight thread pool efficiently manages worker threads for concurrent task execution.
- **Modern C++:** Utilizes C++17 features such as lambda expressions, `std::chrono`, and smart pointers.
- **Robust Design:** Incorporates RAII and exception-safe patterns for reliable and maintainable code.
- **Single File Format:** All the source code is contained in one file, making it ideal for quick deployment and learning in Visual Studio.

## Getting Started

### Prerequisites
- **Microsoft Visual Studio 2017 or later** with the **C++ Desktop Development** workload installed.
- Basic knowledge of C++ and familiarity with the Visual Studio environment.

### Setup Instructions

1. **Download and Open in Visual Studio:**
   - Download this project (the single file containing the Concurrent Task Scheduler code).
   - Open Microsoft Visual Studio.
   - Create a new **Console App** project in C++.
   - Replace the contents of the auto-generated `main.cpp` with the code from this project file.

2. **Build the Project:**
   - Go to **Build → Build Solution** or press `Ctrl+Shift+B` to compile the project.

3. **Run the Application:**
   - Run the project using **Debug → Start Without Debugging** or press `Ctrl+F5`.
   - A console window will appear showing scheduled tasks executing (e.g., messages like "Task 1 executed after 1 second", etc.).

## Code Overview
The single-file implementation includes:
- **Thread Pool Implementation:** Manages a pool of worker threads to execute tasks concurrently.
- **Task Scheduler:** Provides methods to schedule tasks either after a delay or at a specific time.
- **Demo Tasks:** Sample tasks are scheduled to illustrate the scheduler's capabilities.
- **Main Function:** Initializes the scheduler, sets up demo tasks, waits for execution, and then gracefully shuts down the scheduler and thread pool.

## Usage Example
When you run the application, you should see output similar to the following:

These messages confirm that tasks are being scheduled and executed as intended. Once all tasks are processed, the scheduler cleans up resources and the application exits.

## Extending the Project
- **Adding New Tasks:** Modify the main function to schedule additional tasks or implement new scheduling policies.
- **Enhancing Functionality:** Integrate logging, error handling, or more complex task management features.
- **Modular Expansion:** Although implemented as a single file for simplicity, the design easily lends itself to being split into multiple modules for larger projects.

## Contributing
Contributions to improve this project are welcome! If you have suggestions, bug fixes, or enhancements:
- Fork the repository.
- Make your changes.
- Submit a pull request with detailed descriptions of your updates.

## License
This project is licensed under the MIT License. You are free to use, modify, and distribute this code according to the license terms.

## Final Notes
This single-file **Concurrent Task Scheduler** project is an excellent starting point for exploring advanced C++ concepts such as concurrency and scheduling in a real-world context. Whether you are learning C++ or developing professional applications, this project provides a solid foundation to build upon.

Happy Coding!
