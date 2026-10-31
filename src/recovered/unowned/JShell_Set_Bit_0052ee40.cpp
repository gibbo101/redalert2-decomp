// Set_Bit (0x0052EE40): sets or clears one bit of a packed bit array.
#include "shared/jshell.hpp"

void __fastcall Set_Bit(void *array, int bit, int value)
{
    unsigned char mask = (unsigned char)(1 << (bit % 8));

    if (value != 0) {
        *((unsigned char *)array + (bit / 8)) |= mask;
    } else {
        *((unsigned char *)array + (bit / 8)) &= (unsigned char)~mask;
    }
}
