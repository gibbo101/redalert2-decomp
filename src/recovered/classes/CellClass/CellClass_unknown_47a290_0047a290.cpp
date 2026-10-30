// int CellClass::unknown_47a290() const (0x0047A290): the height of the top
// of the cell: the ground height at its middle plus, with a building, the
// height (Z) of its type's slot 31 dimensions, or else 0x55 when an occupant
// stands at the spot (0, 0) (name hypothesis).
#include "shared/cell.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?unknown_4706c0@CellClass@@QBEHABUPoint2D@@@Z=004706c0
// @ref ?unknown_471660@CellClass@@QBEPAVObjectClass@@ABUPoint2D@@_NPAV2@@Z=00471660
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"

int CellClass::unknown_47a290() const
{
    int height;
    {
        Point2D center = Point2D(128, 128);
        height = unknown_4706c0(center);
    }
    BuildingClass *building = (BuildingClass *)unknown_4717b0();
    if (building != 0) {
        CoordStruct dimensions = building->Type->unknown_slot31();
        height += dimensions.Z;
    } else if (unknown_471660(Point2D(0, 0), false, 0) != 0) {
        height += 0x55;
    }
    return height;
}
