// void TechnoClass::unknown_slot265() (0x006D7500, slot 265)
// Map call 0x00631AF0 with +0x1A0/+0x1A4; clears unknown_37b.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void TechnoClass::unknown_slot265()
{
    Map.Unknown_00631AF0(this, unknown_1a0);
    unknown_37b = false;
}
