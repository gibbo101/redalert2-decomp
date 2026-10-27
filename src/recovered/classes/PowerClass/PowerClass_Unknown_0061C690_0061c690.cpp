// int PowerClass::Unknown_0061C690() (0x0061C690)
// The three counters' total, capped at Unknown_0061C5F0, as a share of it
// times 5. No direct callers (inlined elsewhere).
#include "shared/power.hpp"
// @ref __real@8@4001a000000000000000=0079c278
// @ref __ftol=0077f110

int PowerClass::Unknown_0061C690()
{
    int value = Unknown_0061C5F0();
    int total = unknown_1530 + unknown_152c + unknown_1528;
    if (total > value) {
        total = value;
    }
    return (int)((double)total / value * 5.0);
}
// @ref ?Unknown_0061C5F0@PowerClass@@QAEHXZ=0061c5f0
