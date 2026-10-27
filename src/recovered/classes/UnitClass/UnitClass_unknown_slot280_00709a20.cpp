// void UnitClass::unknown_slot280(int arg1) (0x00709A20, slot 280)
// arg1 is a techno whose owned object at +0x208 moves to this unit (the
// IFV gunner hand-over; hypothesis): selects weapon 7, and when the
// donor's +0x244 timer was still running restarts this unit's (slot 187
// with 7, counted at +0x310). Either way the donor type's IFVMode weapon is
// then selected (the call is outside the guards).
#include "shared/unit.hpp"
// @ref ?unknown_6d83f0@TechnoClass@@QAEXH@Z=006d83f0

void UnitClass::unknown_slot280(int arg1)
{
    TechnoClass *from = (TechnoClass *)arg1;
    UnknownTechno208 *object = from->unknown_208;
    if (object) {
        int running = 0;
        if (from->unknown_244.Value()) {
            running = 1;
        }
        unknown_208 = object;
        object->unknown_24 = (int)this;
        from->unknown_208 = 0;
        unknown_6d83f0(7);
        if (running) {
            unknown_310++;
            unknown_244 = CDTimerClass<FrameTimerClass>(unknown_slot187(7));
        }
    }
    unknown_6d83f0(from->unknown_slot32()->IFVMode);
}
