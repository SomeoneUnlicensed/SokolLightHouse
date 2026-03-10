.section .text
.global calculate_crc16
.type calculate_crc16, %function

// uint16_t calculate_crc16(const uint8_t *data [x0], uint32_t length [x1])
calculate_crc16:
    mov w2, #0xFFFF       // Initial CRC value
    cbz x1, done          // If length is 0, return 0xFFFF

loop:
    ldrb w3, [x0], #1     // Load byte and increment pointer
    eor w2, w2, w3        // CRC ^= byte
    
    // Manual bit-by-bit calculation (8 bits)
    mov w4, #8
bit_loop:
    lsr w5, w2, #1        // next = crc >> 1
    tst w2, #1            // check LSB
    mov w6, #0xA001       // polynomial
    csel w2, w5, w5, eq   // If LSB == 0, crc = next
    eor w7, w5, w6        // if LSB == 1, crc = next ^ poly
    csel w2, w7, w5, ne
    
    subs w4, w4, #1
    b.ne bit_loop

    subs x1, x1, #1
    b.ne loop

done:
    and w0, w2, #0xFFFF   // Ensure 16-bit result
    ret
