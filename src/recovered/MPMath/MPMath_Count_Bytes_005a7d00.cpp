// XMP_Count_Bytes(digit const *number, int precision) (0x005A7D00)
// Counts the leading non-zero bytes from the low end (original behaviour).
#include "shared/mpmath.hpp"

int __fastcall XMP_Count_Bytes(digit const *number, int precision)
{
    unsigned char const *ptr = (unsigned char const *)number;
    int count = 0;
    for (unsigned index = 0; index < precision * sizeof(digit); index++) {
        if (!ptr[index]) {
            break;
        }
        count++;
    }
    return count;
}
