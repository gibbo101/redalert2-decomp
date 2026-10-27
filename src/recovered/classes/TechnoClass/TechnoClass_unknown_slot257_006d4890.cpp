// bool TechnoClass::unknown_slot257() (0x006D4890, slot 257)
// Whether the timer at +0x130 has expired.
#include "shared/techno.hpp"

bool TechnoClass::unknown_slot257()
{
    return unknown_130.Value() == 0;
}
