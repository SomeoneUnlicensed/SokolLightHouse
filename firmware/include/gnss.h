#ifndef GNSS_H
#define GNSS_H

#include <string>
#include <vector>

struct GNSSData {
    double latitude;
    double longitude;
    float altitude;
    float speed;
    bool valid;
};

class GNSSManager {
public:
    GNSSManager(const std::string& device = "/dev/ttyAMA0");
    ~GNSSManager();

    bool openDevice();
    GNSSData parseNMEA();

private:
    int fd;
    std::string devicePath;
    char buffer[1024];
};

#endif // GNSS_H
