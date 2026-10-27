// bool HouseClass::unknown_func_4e7e80() (0x004E7E80)
// Sets the +0x13E flag and restarts the +0x1E0 timer at zero unless one of
// the +0x13E..+0x140 flags is already set; returns the +0x13E flag.
#include "shared/techno.hpp"

bool HouseClass::unknown_func_4e7e80()
{
    if (!unknown_13f && !unknown_13e && !unknown_140) {
        unknown_13e = true;
        unknown_1e0 = CDTimerClass<FrameTimerClass>(0);
    }
    return unknown_13e;
}
