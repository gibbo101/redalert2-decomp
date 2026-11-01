// bool ParasiteClass::Grapple_Frame_006066B0() (0x006066B0)
// Advances the grapple animation one tick: each state shows ten frames per
// victim direction (states 0-1 at three ticks a frame from frame 0, state 2
// from frame 80 and the others from frame 160 at four ticks). True once the
// tenth frame has passed.
#include "shared/foot.hpp"
#include "shared/anim.hpp"
#include "shared/parasite.hpp"

bool ParasiteClass::Grapple_Frame_006066B0()
{
    UnknownFacingDir dir = unknown_28->unknown_2e0.Current();
    int base;
    int delay;
    switch (unknown_48) {
    case 0:
    case 1:
        base = 0;
        delay = 3;
        break;
    case 2:
        base = 0x50;
        delay = 4;
        break;
    default:
        base = 0xA0;
        delay = 4;
        break;
    }
    if (++unknown_50 >= delay) {
        unknown_50 = 0;
        if (++unknown_4c >= 10) {
            return true;
        }
        if (Victim != 0) {
            ((AnimClass *)Victim)->Set_Rate(0x80);
            ((AnimClass *)Victim)->Stage = unknown_4c + Dir_To_8(dir) * 10 + base;
        }
    }
    return false;
}
