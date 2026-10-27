// bool TechnoClass::unknown_6d4310() (0x006D4310)
// When 0x006D4180 allows it: stamps +0x3F4 with the frame and asks slot 209
// about the current coordinate; a changed +0x228 then sets +0x404.
#include "shared/techno.hpp"
// @ref ?unknown_6d4180@TechnoClass@@QAE_NXZ=006d4180
// @ref ?Frame@@3HA=00a40d2c

bool TechnoClass::unknown_6d4310()
{
    bool result = false;
    if (unknown_6d4180()) {
        unknown_3f4 = Frame;
        AbstractClass *target = unknown_228;
        CoordStruct coord = Coord;
        result = unknown_slot209(&coord, 1);
        if (result && unknown_228 != target) {
            unknown_404 = true;
        }
    }
    return result;
}
