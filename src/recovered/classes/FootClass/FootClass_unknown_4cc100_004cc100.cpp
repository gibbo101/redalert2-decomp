// Cell FootClass::unknown_4cc100(int radius) (0x004CC100)
// The unit's own cell when it passes 0x004CC260; otherwise, ring by ring
// out to the radius, the last cell on the first ring that has one that
// passes (the zero cell when none does).
#include "shared/foot.hpp"
// @ref ?unknown_4cc260@FootClass@@QAE_NAAVCell@@HH@Z=004cc260

Cell FootClass::unknown_4cc100(int radius)
{
    Cell found = unknown_geometry_k;
    Cell center = Coord_Cell(Center_Coord());
    if (unknown_4cc260(center, 0, 0)) {
        return center;
    }
    for (int ring = 1; ring < radius; ring++) {
        for (int index = -ring; index <= ring; index++) {
            Cell cell = center;
            if (unknown_4cc260(cell, index, -ring)) {
                found = cell;
            }
            cell = center;
            if (unknown_4cc260(cell, index, ring)) {
                found = cell;
            }
            cell = center;
            if (unknown_4cc260(cell, -ring, index)) {
                found = cell;
            }
            cell = center;
            if (unknown_4cc260(cell, ring, index)) {
                found = cell;
            }
        }
        if (found.X != unknown_geometry_k.X || found.Y != unknown_geometry_k.Y) {
            break;
        }
    }
    return found;
}
