# SokolLightHouse Assembly Instructions

This document provides a guide for assembling the SokolLightHouse hardware.

## Components Required

- **Raspberry Pi 5**: High-performance processing unit (ARMv8-A Cortex-A76).
- **u-blox NEO-M8N GNSS Module**: Provides real-time positioning via UART.
- **Semtech SX1278 LoRa Transceiver**: For long-range transmission at 433 MHz.
- **Passive Cooling Solution**: Critical for reliability under high-stress conditions.
- **3.3V Power Supply**: Ensure stable power to all peripherals.

## Hardware Connections

### GNSS (NEO-M8N) to Raspberry Pi 5
| GNSS Pin | RPi GPIO (Physical) | RPi Function |
|----------|--------------------|--------------|
| VCC      | Pin 1 (3.3V)       | Power        |
| GND      | Pin 6 (GND)        | Ground       |
| TX       | Pin 10 (GPIO 15)   | UART RX      |
| RX       | Pin 8 (GPIO 14)    | UART TX      |

### LoRa (SX1278) to Raspberry Pi 5
| LoRa Pin | RPi GPIO (Physical) | RPi Function |
|----------|--------------------|--------------|
| VCC      | Pin 17 (3.3V)      | Power        |
| GND      | Pin 25 (GND)       | Ground       |
| MOSI     | Pin 19 (GPIO 10)   | SPI MOSI     |
| MISO     | Pin 21 (GPIO 9)    | SPI MISO     |
| SCK      | Pin 23 (GPIO 11)   | SPI SCLK     |
| NSS (CS) | Pin 24 (GPIO 8)    | SPI CE0      |
| DIO0     | Pin 22 (GPIO 25)   | Interrupt    |

## Pinout Diagram

![SokolLightHouse Pinout Diagram](pinout_diagram.png)

## Assembly Steps

1.  **Mount Passive Cooling**: Install a high-quality aluminum heatsink on the Raspberry Pi 5.
2.  **Connect GNSS Module**: Use short jumper wires for UART connection to minimize EMI.
3.  **Connect LoRa Module**: Ensure correct SPI wiring. Use a 433 MHz tuned antenna.
4.  **Power Check**: Before booting Alpine for SAR, verify that all 3.3V and GND pins are correctly seated.
5.  **Antenna Placement**: Place the GNSS antenna with a clear view of the sky and the LoRa antenna vertically for maximum range.

## Software Configuration

The service is pre-configured to use:
- `/dev/ttyAMA0` for GNSS communication.
- `/dev/spidev0.0` for LoRa transmission.
