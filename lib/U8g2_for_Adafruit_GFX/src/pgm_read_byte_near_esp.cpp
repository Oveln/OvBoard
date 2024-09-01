#include "pgm_read_byte_near_esp.h"

uint8_t pgm_read_byte_near_esp(const uint8_t* addr) {
    uint32_t bytes;
    bytes = *(uint32_t*)((uint32_t)addr & ~3);
    return ((uint8_t*)&bytes)[(uint32_t)addr & 3];
}