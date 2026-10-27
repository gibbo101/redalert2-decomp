// int BuildingClass::unknown_4521e0(int arg1) (0x004521E0)
// The slot 254 value, adjusted by 0x006D86F0 when slot 203 holds (slot 79
// expands the same pair).
#include "shared/building.hpp"
// @ref ?unknown_6d86f0@TechnoClass@@QAEHH@Z=006d86f0

int BuildingClass::unknown_4521e0(int arg1)
{
    int value = unknown_slot254(arg1);
    if (unknown_slot203()) {
        value = unknown_6d86f0(value);
    }
    return value;
}
