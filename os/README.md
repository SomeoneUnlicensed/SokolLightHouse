Alpine for SAR
Project Identifier: SomeoneUnlicensed/SokolLightHouse-OS

Base Distribution: Alpine Linux v3.x (aarch64)

Target Hardware: Raspberry Pi 5 (Broadcom BCM2712)

Description
Alpine for SAR is a specialized, hardened Linux distribution designed specifically for the SokolLightHouse emergency positioning system. It provides a minimal, high-performance execution environment for the C++/ASM control service, prioritizing filesystem integrity and deterministic hardware access.

Core Technical Specifications
1. Diskless Operational Mode
The system is configured to run entirely from volatile memory (RAM).

Boot Sequence: The kernel and initramfs are loaded into RAM; the storage media (SD/NVMe) is unmounted immediately after the boot process is complete.

Resilience: This architecture eliminates the risk of filesystem corruption (IO errors) caused by sudden power loss, extreme vibration, or mechanical impact.

Logging: System logs and telemetry buffers are managed via ZRAM to prevent wear on flash storage and ensure high-speed write operations.

2. Hardened Kernel and Minimal Userland
The Linux kernel has been stripped of all non-essential modules to optimize performance and minimize electromagnetic interference (EMI).

Disabled Subsystems: Bluetooth stack, Wi-Fi drivers, Sound (ALSA), Graphics (DRM/KMS), and standard USB HID drivers.

Optimization: Compiled with -march=armv8-a+crc+crypto to leverage the Cortex-A76 instruction set for cryptographic and checksum operations.

C Library: Utilizes musl libc for a reduced memory footprint and faster execution compared to standard glibc.

3. Hardware Abstraction and Peripheral Access
GPIO/UART/SPI: Configured via config.txt and device tree overlays to provide direct, low-latency access for the SokolLightHouse control service.

Clock Management: Fixed CPU and bus frequencies to ensure stable timing for the SPI-linked LoRa transceiver and UART-linked GNSS module.

Filesystem Structure
/bin, /sbin: Minimal BusyBox-based binaries.

/opt/sokol/: Primary directory for the SokolLightHouse control service and binary assets.

/etc/init.d/: Minimalist OpenRC init scripts for rapid service initialization (sub-3 second boot time to application start).

Deployment
Image Generation
To generate the .iso or .img deployment file:

Bash

./scripts/build_alpine_sar.sh --target rpi5
Installation
Flash the resulting image to a microSD card (Class 10 or higher recommended).

Insert into Raspberry Pi 5.

The system will auto-boot into the SAR environment and initialize the emergency beacon service.

Security and Integrity
Read-Only Root: The root filesystem is immutable during runtime.

Service Isolation: The control service runs with elevated real-time priority (SCHED_FIFO) to prevent preemption by background system tasks.

Maintenance
System updates are performed via image replacement. Since the OS operates in a diskless state, no on-disk configuration persistence is maintained unless explicitly defined in the .apkovl overlay. This repository will not futherly be supported, please note this. 

Credits
Part of the SokolLightHouse project.

Letunovskiy Vladimir 
ALL RIGHT RESERVED