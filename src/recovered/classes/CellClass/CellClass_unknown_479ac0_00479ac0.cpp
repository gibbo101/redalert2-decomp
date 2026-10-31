// int CellClass::unknown_479ac0(CoordStruct const &origin) const (0x00479AC0): Westwood's
// Bounce_Direction. The facing from origin's cell to this one (a table by the offset), turned one
// step toward the side whose neighbour stands two levels above origin's cell when only one does.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_facing_lookup_7d2c44@@3PAHA=007d2c44
// The facing by dx + 3 * dy (0x007D2C44, a function-local static of the original; not range checked).
extern int unknown_facing_lookup_7d2c44[];
int CellClass::unknown_479ac0(CoordStruct const &xorigin) const
{
    Cell origin = Map[xorigin].MapCoords;

    int dx = MapCoords.X - origin.X;
    int dy = MapCoords.Y - origin.Y;

    int base = unknown_facing_lookup_7d2c44[(MapCoords.X - origin.X) + 3 * (MapCoords.Y - origin.Y)];
    if (dx != 0 && dy != 0) {
        bool left;
        bool right;
        if (dx == dy) {
            left = Map[origin + Cell(dx, 0)].unknown_11b >= Map[xorigin].unknown_11b + 2;
            right = Map[origin + Cell(0, dy)].unknown_11b >= Map[xorigin].unknown_11b + 2;
        } else {
            left = Map[origin + Cell(dy, 0)].unknown_11b >= Map[xorigin].unknown_11b + 2;
            right = Map[origin + Cell(0, dx)].unknown_11b >= Map[xorigin].unknown_11b + 2;
        }
        if (left) {
            if (!right) {
                base = (base - 1) & 7;
            }
        } else if (right) {
            base++;
        }
    }
    return base;
}
