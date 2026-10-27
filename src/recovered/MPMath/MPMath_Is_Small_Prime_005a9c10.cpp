// XMP_Is_Small_Prime(digit const *candidate, int precision) (0x005A9C10)
// Whether the number is in the small-prime table (binary search).
#include "shared/mpmath.hpp"

// Binary search of the prime table.
static inline unsigned short const *Search_Primes(unsigned short key)
{
    unsigned short const *base = primeTable;
    int num = sizeof(primeTable) / sizeof(primeTable[0]);
    while (num > 0) {
        int half = num / 2;
        unsigned short const *mid = base + half;
        if (*mid > key) {
            num = half;
        } else if (*mid == key) {
            return mid;
        } else {
            base = mid + 1;
            num = num - half - 1;
        }
    }
    return 0;
}

bool __fastcall XMP_Is_Small_Prime(digit const *candidate, int precision)
{
    if (XMP_Significance(candidate, precision) > 1) {
        return false;
    }

    if (*candidate > primeTable[sizeof(primeTable) / sizeof(primeTable[0]) - 1]) {
        return false;
    }

    return Search_Primes((unsigned short)*candidate) != 0;
}
