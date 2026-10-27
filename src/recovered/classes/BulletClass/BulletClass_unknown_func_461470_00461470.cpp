// void BulletClass::unknown_func_461470() (0x00461470)
// Retargets the bullet at the cell under its target (cleared when the
// target is in limbo-like state or the cell is the zero cell).
#include "shared/bullet.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void BulletClass::unknown_func_461470()
{
    Cell cell = Coord_Cell(Target->Center_Coord());
    if (unknown_a40774 == 0 && !Target->unknown_slot21() && (cell.X != unknown_geometry_k.X || cell.Y != unknown_geometry_k.Y)) {
        Target = (AbstractClass *)&Map[cell];
        return;
    }
    Target = 0;
}
