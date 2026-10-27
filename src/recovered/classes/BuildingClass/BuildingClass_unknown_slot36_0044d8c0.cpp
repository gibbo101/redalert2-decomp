// bool BuildingClass::unknown_slot36() (0x0044D8C0, slot 36)
// False without strength, without the type flag at +0x121D or when slot 31
// holds; otherwise the techno answer.
#include "shared/building.hpp"
// @ref ?unknown_slot36@TechnoClass@@UAE_NXZ=006cd690

bool BuildingClass::unknown_slot36()
{
    if (!Strength) {
        return false;
    }
    if (!Type->ClickRepairable) {
        return false;
    }
    if (unknown_slot31()) {
        return false;
    }
    return TechnoClass::unknown_slot36();
}
