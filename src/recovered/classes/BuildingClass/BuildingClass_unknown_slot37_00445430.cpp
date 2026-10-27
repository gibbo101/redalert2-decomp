// bool BuildingClass::unknown_slot37() (0x00445430, slot 37)
// False for an unsellable type; true while a buildup is shown and +0x42C is
// set outside missions 18/19, or for a firestorm wall whose owner lacks
// +0x142 (meaning hypotheses).
#include "shared/building.hpp"

bool BuildingClass::unknown_slot37()
{
    if (!Type->Unsellable) {
        if (unknown_5b9 && unknown_42c && unknown_slot91() != 19 && unknown_slot91() != 18) {
            return true;
        }
        if (Type->FirestormWall && !House->unknown_142) {
            return true;
        }
    }
    return false;
}
