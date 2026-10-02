# System Resource Monitor

## 1. Project Introduction
This project is a concurrent system resource monitoring tool bridging user-space C++ applications and kernel-space Linux Device Drivers. It reads standard OS metrics alongside simulated hardware sensor data.

## 2. System Architecture
*   **Kernel Space:** A custom character device driver (`sensor.ko`) utilizing kernel timers (`jiffies`) to simulate dynamic hardware data and expose it via `/dev/dummy_sensor`.
*   **User Space:** A C++ monitoring daemon that utilizes POSIX system calls (`open`, `read`) to communicate with the kernel, and standard file streams to parse `/proc/stat`.
*   **Concurrency:** Utilizes `std::thread` to read CPU and hardware metrics simultaneously, protected by `std::mutex` to prevent terminal UI race conditions.

## 3. Project Achievements
*   Successfully compiled and loaded a custom Linux Kernel Module (LKM) in an Ubuntu ARM64 environment.
*   Achieved secure user-to-kernel memory transfer using `copy_to_user()`.
*   Implemented a multithreaded C++ architecture demonstrating advanced system programming concepts.
*   Maintained continuous Git version control throughout the software development lifecycle.
