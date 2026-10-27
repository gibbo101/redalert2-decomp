// void BuildingClass::unknown_4397c0() (0x004397C0)
// Calls slot 60 on each of the eight objects at +0x49C and clears them.
// No direct callers: inlined into the destructor, which is the evidence for
// the call there.
#include "shared/building.hpp"

void BuildingClass::unknown_4397c0()
{
    for (int index = 0; index < 8; index++) {
        if (unknown_49c[index]) {
            unknown_49c[index]->unknown_slot60();
            unknown_49c[index] = 0;
        }
    }
}
