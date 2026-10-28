// bool CaptureManagerClass::Can_Capture(TechnoClass *target) (0x00467F80)
// A target can be taken over unless it is missing, already belongs to the
// owner's house, its type is ImmuneToPsionics, something already controls
// it (+0x234) or slot 203 holds (names after YR's CaptureManagerClass).
#include "shared/capture_manager.hpp"
#include "shared/techno.hpp"

bool CaptureManagerClass::Can_Capture(TechnoClass *target)
{
    if (target == 0) {
        return false;
    }
    if (target->Owning_House() == Owner->Owning_House()) {
        return false;
    }
    if (target->unknown_slot32()->ImmuneToPsionics) {
        return false;
    }
    if (target->unknown_234 != 0) {
        return false;
    }
    if (target->unknown_slot203()) {
        return false;
    }
    return true;
}
