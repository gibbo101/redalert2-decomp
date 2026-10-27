// XMP_Fetch_Prime_Size() (0x005A7540)
// Number of entries in the prime table.
#include "shared/mpmath.hpp"

int __fastcall XMP_Fetch_Prime_Size()
{
    return sizeof(primeTable) / sizeof(primeTable[0]);
}
