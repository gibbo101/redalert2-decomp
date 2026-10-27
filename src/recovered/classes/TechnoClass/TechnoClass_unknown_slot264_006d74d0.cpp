// void TechnoClass::unknown_slot264() (0x006D74D0, slot 264)
// Map call 0x00631910 with +0x1A0/+0x1A4; sets unknown_37b.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00631910@RadarClass@@QAEXPAVTechnoClass@@UPoint2D@@@Z=00631910

void TechnoClass::unknown_slot264()
{
    Map.Unknown_00631910(this, unknown_1a0);
    unknown_37b = true;
}
