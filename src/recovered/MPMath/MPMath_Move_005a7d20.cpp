// XMP_Move(digit *dest, digit const *source, int precision) (0x005A7D20)
#include "shared/mpmath.hpp"
#include "shared/crt_memory.hpp"

void __fastcall XMP_Move(digit *dest, digit const *source, int precision)
{
    memcpy(dest, source, precision * sizeof(digit));
}
