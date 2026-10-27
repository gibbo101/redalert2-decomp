// void RadarClass::Unknown_006331E0(bool flag) (0x006331E0)
// Asks for a radar redraw (+0x14D5), a complete one (+0x14D6) when flag is set.
#include "shared/radar.hpp"

void RadarClass::Unknown_006331E0(bool flag)
{
    unknown_14d5 = true;
    unknown_14d6 = unknown_14d6 || flag;
}
