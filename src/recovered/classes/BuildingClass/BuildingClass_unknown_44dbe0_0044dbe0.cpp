// void BuildingClass::unknown_44dbe0() (0x0044DBE0)
// Outside a movie (unknown_a40774 clear), a laser fence post that is active
// (+0x7D) and not selected out (+0x76 clear) refreshes its four directions
// (0044DFC0 with 0, 2, 4, 6) and then the field (0044E5A0).
#include "shared/building.hpp"
// @ref ?unknown_44dfc0@BuildingClass@@QAEXH@Z=0044dfc0
// @ref ?unknown_44e5a0@BuildingClass@@QAEXH@Z=0044e5a0

void BuildingClass::unknown_44dbe0()
{
    if (!unknown_a40774 && Type->LaserFencePost && unknown_7d && !unknown_76) {
        unknown_44dfc0(0);
        unknown_44dfc0(2);
        unknown_44dfc0(4);
        unknown_44dfc0(6);
        unknown_44e5a0(1);
    }
}
