#ifndef LORA_H
#define LORA_H

#include <string>
#include <stdint.h>

class LoRaManager {
public:
    LoRaManager(const std::string& device = "/dev/spidev0.0");
    ~LoRaManager();

    bool openDevice();
    void sendPacket(const uint8_t* data, uint32_t size);

private:
    int fd;
    std::string devicePath;
    uint8_t spiTransfer(uint8_t address, uint8_t value);
    void setMode(uint8_t mode);
};

#endif // LORA_H
