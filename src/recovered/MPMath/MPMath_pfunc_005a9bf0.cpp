// pfunc(void const *key, void const *element) (0x005A9BF0)
// Compares two prime-table entries (for the binary search).
#include "shared/mpmath.hpp"

int __fastcall pfunc(void const *key, void const *element)
{
    if (*(unsigned short const *)key < *(unsigned short const *)element) {
        return -1;
    }
    return *(unsigned short const *)key > *(unsigned short const *)element;
}
