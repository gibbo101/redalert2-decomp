// bool TechnoClass::unknown_slot120() (0x006CD880, slot 120)
// Restores the suspended mission and the +0x22C value.
#include "shared/techno.hpp"
// @ref ?unknown_slot120@MissionClass@@UAE_NXZ=00594d80

bool TechnoClass::unknown_slot120()
{
    if (MissionClass::unknown_slot120()) {
        unknown_slot220(unknown_22c);
        return true;
    }
    return false;
}
