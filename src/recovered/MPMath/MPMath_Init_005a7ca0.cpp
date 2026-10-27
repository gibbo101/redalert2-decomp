// XMP_Init(digit *number, digit value, int precision) (0x005A7CA0)
#include "shared/mpmath.hpp"
#include "shared/crt_memory.hpp"

void __fastcall XMP_Init(digit *number, digit value, int precision)
{
    memset(number, '\0', precision * sizeof(digit));
    *number = value;
}
