// bool InfantryClass::unknown_slot291() (0x00504AE0, slot 291)
// Plays slot 311 (28 while deploying (sequences 27-30), 2 when prone,
// else 0), records in +0x5C4 whether slot 101 reports the current cell
// occupied in the eight-way facing, then FootClass's slot 291.
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Unknown_005D47D0@ObjectClass@@QBEHXZ=005d47d0
// @ref ?unknown_slot291@FootClass@@UAE_NXZ=004c4b60

bool InfantryClass::unknown_slot291()
{
    if (unknown_5090d0()) {
        unknown_slot311(28, 0, 0);
    } else if (unknown_5c3) {
        unknown_slot311(2, 0, 0);
    } else {
        unknown_slot311(0, 0, 0);
    }
    int facing = Dir_To_8(unknown_2e0.Current());
    CoordStruct coord = Coord;
    if (unknown_slot101(&Map[coord], facing, Unknown_005D47D0(), 0, 1) == 0) {
        unknown_5c4 = false;
    } else {
        unknown_5c4 = true;
    }
    return FootClass::unknown_slot291();
}
