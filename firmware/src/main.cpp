#include <iostream>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include "../include/gnss.h"
#include "../include/lora.h"
#include "../include/crc16.h"

bool running = true;

void signalHandler(int signum) {
    running = false;
}

int main() {
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    GNSSManager gnss;
    LoRaManager lora;

    if (!gnss.openDevice()) {
        std::cerr << "Failed to open GNSS device" << std::endl;
        return 1;
    }

    if (!lora.openDevice()) {
        std::cerr << "Failed to open LoRa device" << std::endl;
        return 1;
    }

    std::cout << "SokolLightHouse Service Started" << std::endl;

    while (running) {
        GNSSData data = gnss.parseNMEA();

        if (data.valid) {
            uint8_t packet[20];
            std::memcpy(&packet[0], &data.latitude, 8);
            std::memcpy(&packet[8], &data.longitude, 8);
            
            uint16_t crc = calculate_crc16(packet, 16);
            std::memcpy(&packet[16], &crc, 2);

            lora.sendPacket(packet, 18);
            
            std::cout << "Sent: Lat=" << data.latitude << ", Lon=" << data.longitude << ", CRC=" << std::hex << crc << std::endl;
        }

        sleep(5); // Send interval
    }

    std::cout << "SokolLightHouse Service Stopped" << std::endl;
    return 0;
}
