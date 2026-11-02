// bool CaptureManagerClass::Capture(TechnoClass *target) (0x00467FF0)
// Releases the object held so far (back to the house it came from, +0x28),
// then takes over a capturable techno: it changes to the owner's house
// (slot 222; on refusal nothing is held), records the owner as its
// controller (+0x234), leaves its team, drops its targets and goes to
// mission 5; an attached +0x208 object lets go of its target.
#include "shared/capture_manager.hpp"
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/techno.hpp"

bool CaptureManagerClass::Capture(TechnoClass *target)
{
    if (unknown_24 != 0) {
        unknown_24->unknown_234 = 0;
        unknown_24->unknown_slot222(unknown_28, true);
        unknown_24 = 0;
        unknown_28 = 0;
    }
    bool capture = target != 0 && target->AbstractFlags.IsTechno && Can_Capture(target);
    if (!capture) {
        return false;
    }
    unknown_28 = target->Owning_House();
    if (!target->unknown_slot222(Owner->Owning_House(), true)) {
        unknown_28 = 0;
        return false;
    }
    unknown_24 = target;
    target->unknown_234 = Owner;
    if (unknown_24 != 0 && unknown_24->AbstractFlags.IsFoot && ((FootClass *)unknown_24)->Team != 0) {
        ((FootClass *)unknown_24)->Team->Unknown_006B8FB0((FootClass *)unknown_24, -1, 0);
    }
    unknown_24->unknown_slot260(0, true);
    unknown_24->unknown_slot220(0);
    unknown_24->unknown_6d6e50(0);
    unknown_24->unknown_slot116(5, true);
    if (unknown_24->unknown_208 != 0 && unknown_24->unknown_208->unknown_28 != 0) {
        unknown_24->unknown_208->unknown_6e2500();
    }
    return true;
}
