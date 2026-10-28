// bool MechLocomotionClass::unknown_592f70(CoordStruct const &coord) (0x00592F70)
// Heads for a coordinate on the ground (raised by the bridge height on a
// bridge cell well below the object): clears the old head-to mark, takes
// the coordinate when its cell can be entered, and marks the head-to cell
// (or, when none and +0x7D is set, the object's own cell). True when a
// head-to coordinate was taken.
#include "shared/mech_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_coord_a70b18@@3UCoordStruct@@A=00a70b18
// @ref ?unknown_476cc0@CellClass@@QAE_NPAVObjectClass@@@Z=00476cc0

bool MechLocomotionClass::unknown_592f70(CoordStruct const &coord)
{
    CoordStruct to = coord;
    if (to != unknown_coord_a70b18) {
        to.Z = Map.Unknown_0055A280(to);
        if (Loco_Cell(coord)->Flags & 0x100) {
            if (Object_Coord(LinkedTo).Z > to.Z + unknown_geometry_g * 2 + unknown_geometry_g) {
                to.Z += unknown_geometry_j;
            }
        }
    }
    if (unknown_24 != unknown_coord_a70b18) {
        LinkedTo->unknown_slot59(unknown_24);
    }
    if (Map[to].unknown_476cc0(LinkedTo) && !LinkedTo->unknown_76) {
        unknown_24 = to;
    } else {
        unknown_24 = unknown_coord_a70b18;
        if (!LinkedTo->unknown_7d) {
            return false;
        }
    }
    if (unknown_24 != unknown_coord_a70b18) {
        LinkedTo->unknown_slot58(unknown_24);
        return true;
    }
    LinkedTo->unknown_slot58(Object_Coord(LinkedTo));
    return false;
}
