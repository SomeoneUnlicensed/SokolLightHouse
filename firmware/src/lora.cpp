#include "../include/lora.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#define REG_FIFO 0x00
#define REG_OP_MODE 0x01
#define REG_PA_CONFIG 0x09
#define REG_FIFO_ADDR_PTR 0x0D
#define REG_FIFO_TX_BASE_ADDR 0x0E
#define REG_PAYLOAD_LENGTH 0x22

#define MODE_SLEEP 0x00
#define MODE_STDBY 0x01
#define MODE_TX 0x03
#define MODE_LONG_RANGE_MODE 0x80

LoRaManager::LoRaManager(const std::string& device) : fd(-1), devicePath(device) {}

LoRaManager::~LoRaManager() {
    if (fd != -1) close(fd);
}

bool LoRaManager::openDevice() {
    fd = open(devicePath.c_str(), O_RDWR);
    if (fd == -1) return false;

    uint8_t mode = SPI_MODE_0;
    uint32_t speed = 500000;
    ioctl(fd, SPI_IOC_WR_MODE, &mode);
    ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

    // Basic LoRa initialization
    setMode(MODE_SLEEP | MODE_LONG_RANGE_MODE);
    setMode(MODE_STDBY);
    
    // Set PA output power
    spiTransfer(REG_PA_CONFIG | 0x80, 0x8F); // PA_BOOST + 17dBm
    
    return true;
}

uint8_t LoRaManager::spiTransfer(uint8_t address, uint8_t value) {
    uint8_t tx[] = {address, value};
    uint8_t rx[2];
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 2,
        .speed_hz = 500000,
        .bits_per_word = 8,
    };
    ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    return rx[1];
}

void LoRaManager::setMode(uint8_t mode) {
    spiTransfer(REG_OP_MODE | 0x80, mode);
}

void LoRaManager::sendPacket(const uint8_t* data, uint32_t size) {
    setMode(MODE_STDBY);
    spiTransfer(REG_FIFO_ADDR_PTR | 0x80, spiTransfer(REG_FIFO_TX_BASE_ADDR, 0));
    
    for (uint32_t i = 0; i < size; i++) {
        spiTransfer(REG_FIFO | 0x80, data[i]);
    }
    
    spiTransfer(REG_PAYLOAD_LENGTH | 0x80, size);
    setMode(MODE_TX);
    
    // Simple wait for TX done (could use DIO0 interrupt for production)
    usleep(100000);
}
