#include "shared/crc_memory.hpp"
extern unsigned long const unknown_crc_table_007d5504[256];
// @ref ?unknown_crc_table_007d5504@@3QBKB=007d5504
unsigned long __fastcall CRC_String_004941d0(char const *string, unsigned long initial)
{
    unsigned long crc = ~initial;
    while (*string != 0) {
        crc = (crc >> 8) ^ unknown_crc_table_007d5504[(unsigned char)*string++ ^ (unsigned char)crc];
    }
    return ~crc;
}
