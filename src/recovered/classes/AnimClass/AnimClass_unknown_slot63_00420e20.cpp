// bool AnimClass::unknown_slot63(Rect *bounds, bool arg2, bool arg3) (0x00420E20)
// Refused while the animation waits out its loop delay; otherwise the
// ObjectClass slot. Needs ObjectClass::unknown_slot63 declared bool
// (0x005D34E0 returns al).
#include "shared/anim.hpp"
// @ref ?unknown_slot63@ObjectClass@@UAE_NHHH@Z=005d34e0

bool AnimClass::unknown_slot63(Rect *bounds, bool arg2, bool arg3)
{
    if (LoopDelay != 0) {
        return false;
    }
    return ObjectClass::unknown_slot63(bounds, arg2, arg3);
}
