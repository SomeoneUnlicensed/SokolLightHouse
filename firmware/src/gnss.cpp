#include "../include/gnss.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <vector>

GNSSManager::GNSSManager(const std::string& device) : fd(-1), devicePath(device) {}

GNSSManager::~GNSSManager() {
    if (fd != -1) close(fd);
}

bool GNSSManager::openDevice() {
    fd = open(devicePath.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) return false;

    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcsetattr(fd, TCSANOW, &options);
    
    return true;
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

GNSSData GNSSManager::parseNMEA() {
    GNSSData data = {0.0, 0.0, 0.0, 0.0, false};
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead <= 0) return data;

    buffer[bytesRead] = '\0';
    std::string nmea(buffer);
    std::istringstream ss(nmea);
    std::string line;

    while (std::getline(ss, line)) {
        if (line.find("$GPRMC") != std::string::npos) {
            auto parts = split(line, ',');
            if (parts.size() >= 7 && parts[2] == "A") {
                data.valid = true;
                // Latitude: DDMM.MMMMM
                double lat = std::stod(parts[3].substr(0, 2)) + std::stod(parts[3].substr(2)) / 60.0;
                if (parts[4] == "S") lat = -lat;
                data.latitude = lat;

                // Longitude: DDDMM.MMMMM
                double lon = std::stod(parts[5].substr(0, 3)) + std::stod(parts[5].substr(3)) / 60.0;
                if (parts[6] == "W") lon = -lon;
                data.longitude = lon;
            }
        }
    }
    return data;
}
