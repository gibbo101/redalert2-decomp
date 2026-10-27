// bool FootClass::unknown_4cb830(int arg1, int arg2) (0x004CB830)
// With nothing at +0x494: the cell chosen by 0x004CB8F0; true when the unit
// already stands there, otherwise slot 260 toward that cell's object
// (false). False when no cell is chosen.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

bool FootClass::unknown_4cb830(int arg1, int arg2)
{
    if (unknown_494 == 0) {
        Cell cell = unknown_4cb8f0(arg1, arg2);
        if (cell.X != unknown_geometry_k.X || cell.Y != unknown_geometry_k.Y) {
            Cell here = Coord_Cell(Center_Coord());
            if (cell.X == here.X && cell.Y == here.Y) {
                return true;
            }
            unknown_slot260((AbstractClass *)&Map[cell], true);
        }
    }
    return false;
}
