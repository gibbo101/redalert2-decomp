// void UnitClass::unknown_slot239() (0x006FBB40, slot 239)
// While a unit that cannot fire on the move is moving, keeps the timer at
// +0x194 from running out (one frame more than it has left); then the
// techno behaviour.
#include "shared/unit.hpp"
// @ref ?unknown_slot239@TechnoClass@@UAEXXZ=006c8290
// @ref __com_issue_error@4=00795940

void UnitClass::unknown_slot239()
{
    if (!Type->MobileFire && Locomotor.Checked()->Is_Moving() && unknown_194.Value() > 0) {
        unknown_194 = CDTimerClass<FrameTimerClass>(unknown_194.Value() + 1);
    }
    TechnoClass::unknown_slot239();
}
