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

## 4. Project Requirements & Development Plan (Stage 2)
**Functional Requirements:**
* The system must read CPU metrics continuously from `/proc/stat`.
* A custom Linux Kernel Module (LKM) must simulate hardware sensor data using kernel timers (`jiffies`).
* The system must expose the sensor data to user space via a character device file (`/dev/dummy_sensor`).

**Non-Functional Requirements:**
* **Concurrency:** The user-space application must use multithreading (`std::thread`) to read data streams concurrently.
* **Thread Safety:** Terminal UI updates must be protected by a mutex (`std::mutex`) to prevent race conditions during printing.
* **Performance:** The monitoring loop must refresh efficiently (every 1 second) without excessive CPU overhead.

## 5. Limitations (Stage 6)
* The hardware sensor is simulated via software (`jiffies`) rather than interfacing with physical GPIO pins or I2C devices.
* The terminal UI relies on clearing the screen (`system("clear")`), which can cause slight visual flickering compared to using a dedicated library.

## 6. Future Improvements (Stage 6)
* Implement `ncurses` for a flicker-free, interactive terminal dashboard.
* Add a feature to log the monitored data to a CSV file or an SQLite database for historical performance analysis.
* Extend the kernel module to read actual hardware thermal zones via ACPI.
