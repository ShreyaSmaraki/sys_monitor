#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>

void readHardwareSensor() {
    char buffer[128];
    int fd = open("/dev/dummy_sensor", O_RDONLY);
    
    if (fd < 0) {
        std::cerr << "Error: Cannot open /dev/dummy_sensor. Is the module loaded?" << std::endl;
        return;
    }
    
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Hardware Status | " << buffer;
    }
    
    close(fd);
}

void readCpuStats() {
    std::ifstream statFile("/proc/stat");
    std::string line;
    
    if (std::getline(statFile, line)) {
        std::cout << "OS CPU Metric   | " << line << std::endl;
    }
}

int main() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "       System Resource Monitor v1.0      " << std::endl;
    std::cout << "=========================================\n" << std::endl;
    
    readCpuStats();
    readHardwareSensor();
    
    std::cout << "\n=========================================\n" << std::endl;
    return 0;
}
