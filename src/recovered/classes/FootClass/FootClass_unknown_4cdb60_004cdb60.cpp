// void FootClass::unknown_4cdb60() (0x004CDB60)
// Replaces +0x4BC by the map's cell object (0x00548070) at the cell of its
// coordinate, stored at +0x4B8.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void FootClass::unknown_4cdb60()
{
    Cell cell = Coord_Cell(unknown_4bc->Center_Coord());
    unknown_4b8 = (AbstractClass *)&Map[cell];
    unknown_4bc = 0;
}
