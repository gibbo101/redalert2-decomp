// bool TemporalClass::Can_Warp_Target(TechnoClass *target) const (0x006E2770)
// A target can be erased when its type is Warpable and slot 203 does not hold (its +0x154 timer
// has run out).
#include "shared/temporal.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"

bool TemporalClass::Can_Warp_Target(TechnoClass *target) const
{
    if (target == 0) {
        return false;
    }
    if (!target->unknown_slot32()->Warpable) {
        return false;
    }
    if (target->unknown_slot203()) {
        return false;
    }
    return true;
}
