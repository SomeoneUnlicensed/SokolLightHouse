#ifndef CRC16_H
#define CRC16_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ARMv8-A Optimized CRC-16 Calculation
uint16_t calculate_crc16(const uint8_t *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif // CRC16_H
