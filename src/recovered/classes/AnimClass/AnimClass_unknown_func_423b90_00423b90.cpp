// bool AnimClass::unknown_func_423b90(Cell const &where) (0x00423B90)
// Whether the animation may come down in a cell: over a bridge-like cell
// (flag 0x100) well above its level only when it is free (+0x128 & 0xE0);
// otherwise not on land types 3, 4 and 10, not on an overlay of the
// +0x278 kind, not on an occupied cell (+0x124 & 0xE0) and not more than
// two levels below the ground.
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_overlay_types_a35de8@@3V?$DynamicVectorClass@PAVUnknownOverlayType@@@@A=00a35de8

bool AnimClass::unknown_func_423b90(Cell const &where)
{
    UnknownAnimCell *cell = (UnknownAnimCell *)&Map[where];
    CoordStruct coord;
    if ((cell->Flags & 0x100) && (coord = Coord, coord.Z - cell->unknown_11b * unknown_geometry_g > unknown_geometry_g * 2)) {
        if (cell->unknown_128 & 0xE0) {
            return false;
        }
    } else {
        if (cell->unknown_ec == 3 || cell->unknown_ec == 10 || cell->unknown_ec == 4) {
            return false;
        }
        if (cell->unknown_44 != -1 && unknown_overlay_types_a35de8[cell->unknown_44]->unknown_278) {
            return false;
        }
        if (cell->unknown_124 & 0xE0) {
            return false;
        }
        coord = Coord;
        if (cell->unknown_11b * unknown_geometry_g - coord.Z > unknown_geometry_g * 2) {
            return false;
        }
    }
    return true;
}
