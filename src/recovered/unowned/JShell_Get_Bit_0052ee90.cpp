// Get_Bit (0x0052EE90): one bit of a packed bit array as 0 or 1.
#include "shared/jshell.hpp"

int __fastcall Get_Bit(void const *array, int bit)
{
    unsigned char mask = (unsigned char)(1 << (bit % 8));
    return (*((unsigned char *)array + (bit / 8)) & mask) != 0;
}
