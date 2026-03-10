# SokolLightHouse Firmware Service

This service is a high-priority C++ application designed for real-time telemetry extraction and transmission.

## Features

- **GNSS Parsing**: Real-time extraction of GPRMC/GPGGA sentences via UART.
- **LoRa Transmission**: SPI-based control for SX1278 transceiver at 433 MHz.
- **ARMv8-A Assembly Optimization**: CRC-16 calculation implemented in assembly for low-latency and deterministic performance.

## Build Instructions

To compile the firmware, you'll need the `aarch64-linux-musl` toolchain:

```bash
make
```

### Components:
- `src/main.cpp`: Main service loop.
- `src/gnss.cpp`: UART interface and NMEA parsing.
- `src/lora.cpp`: SPI interface for SX1278 transceiver.
- `src/crc16.S`: ARMv8-A optimized assembly code for checksum calculation.

## Configuration

- **Device Path**: GNSS module is connected via `/dev/ttyAMA0`.
- **SPI Device**: LoRa transceiver is connected via `/dev/spidev0.0`.
- **Frequency**: 433 MHz (LPD Band).
- **Power**: Configured for 10mW legal limit in the Russian Federation.
