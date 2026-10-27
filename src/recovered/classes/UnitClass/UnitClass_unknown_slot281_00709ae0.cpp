// void UnitClass::unknown_slot281(int arg1) (0x00709AE0, slot 281)
// The reverse of slot 280: this unit's owned object at +0x208 moves to the
// techno arg1 (refreshed through 0x006E2500 when its +0x28 is set); when
// this unit's +0x244 timer was still running the receiver's restarts
// (slot 187 with 0, counted at +0x310). Either way this unit then selects
// weapon 0 (the call is outside the guards).
#include "shared/unit.hpp"
// @ref ?unknown_6e2500@UnknownTechno208@@QAEXXZ=006e2500
// @ref ?unknown_6d83f0@TechnoClass@@QAEXH@Z=006d83f0

void UnitClass::unknown_slot281(int arg1)
{
    TechnoClass *to = (TechnoClass *)arg1;
    if (to && unknown_208) {
        int running = 0;
        if (unknown_244.Value()) {
            running = 1;
        }
        to->unknown_208 = unknown_208;
        unknown_208->unknown_24 = (int)to;
        unknown_208 = 0;
        if (to->unknown_208 && to->unknown_208->unknown_28) {
            to->unknown_208->unknown_6e2500();
        }
        if (running) {
            to->unknown_310++;
            to->unknown_244 = CDTimerClass<FrameTimerClass>(to->unknown_slot187(0));
        }
    }
    unknown_6d83f0(0);
}
