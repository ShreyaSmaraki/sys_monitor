#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <mutex>
#include <cstdlib>

std::mutex console_mutex; // Prevents race conditions when printing

void readHardwareSensor() {
    char buffer[128];
    int fd = open("/dev/dummy_sensor", O_RDONLY);
    
    if (fd >= 0) {
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::lock_guard<std::mutex> lock(console_mutex);
            std::cout << "Hardware Status | " << buffer;
        }
        close(fd);
    } else {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cerr << "Hardware Status | Error: Cannot read sensor.\n";
    }
}

void readCpuStats() {
    std::ifstream statFile("/proc/stat");
    std::string line;
    
    if (std::getline(statFile, line)) {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << "OS CPU Metric   | " << line << std::endl;
    }
}

int main() {
    while (true) {
        system("clear"); // Clears the terminal for a live dashboard effect
        
        std::cout << "\n=========================================" << std::endl;
        std::cout << "       System Resource Monitor v2.0      " << std::endl;
        std::cout << "=========================================\n" << std::endl;
        
        // Spawn threads to read system resources concurrently
        std::thread t1(readCpuStats);
        std::thread t2(readHardwareSensor);
        
        // Wait for both threads to finish
        t1.join();
        t2.join();
        
        std::cout << "\n=========================================" << std::endl;
        std::cout << "Press Ctrl+C to exit..." << std::endl;
        
        sleep(1); // Wait 1 second before refreshing data
    }
    return 0;
}
