// int __fastcall TabClass::Unknown_006A06B0(int value) (0x006A06B0)
// 1 when value lies in [0x00ABE370, 0x00ABE468], else 0.
#include "shared/tab.hpp"
// @ref ?unknown_int_abe370@@3HA=00abe370
// @ref ?unknown_int_abe468@@3HA=00abe468

int __fastcall TabClass::Unknown_006A06B0(int value)
{
    if (value >= unknown_int_abe370 && value <= unknown_int_abe468) {
        return 1;
    }
    return 0;
}
