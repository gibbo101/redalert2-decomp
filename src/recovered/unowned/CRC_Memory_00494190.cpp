#include "shared/crc_memory.hpp"
extern unsigned long const unknown_crc_table_007d5504[256];
// @ref ?unknown_crc_table_007d5504@@3QBKB=007d5504
unsigned long __fastcall CRC_Memory_00494190(void const *buffer, unsigned int length, unsigned long initial)
{
    unsigned char const *data = (unsigned char const *)buffer;
    unsigned long crc = ~initial;
    while (length-- != 0) {
        crc = (crc >> 8) ^ unknown_crc_table_007d5504[(crc & 255) ^ *data++];
    }
    return ~crc;
}
