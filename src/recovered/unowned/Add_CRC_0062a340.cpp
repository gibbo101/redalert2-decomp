// void __fastcall Add_CRC(unsigned long *crc, unsigned long value) (0x0062A340; Red Alert's Add_CRC).
#include "shared/winsock_interface.hpp"

void __fastcall Add_CRC(unsigned long *crc, unsigned long value)
{
    int hibit;

    if ((*crc) & 0x80000000) {
        hibit = 1;
    } else {
        hibit = 0;
    }

    (*crc) <<= 1;
    (*crc) += value;
    (*crc) += hibit;
}
