// int PowerClass::Unknown_0061C6E0() (0x0061C6E0, static)
// One power bar segment per 3 pixels of 0x00ABCD70, rounded up. No direct
// callers (inlined elsewhere).
#include "shared/power.hpp"
// @ref ?unknown_int_abcd70@@3HA=00abcd70

int PowerClass::Unknown_0061C6E0()
{
    return (unknown_int_abcd70 + 3) / 3;
}
