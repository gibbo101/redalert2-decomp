// CellClass *ObjectClass::unknown_slot107() const (0x005D5290)
#include "shared/object_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

CellClass *ObjectClass::unknown_slot107() const
{
    return &Map[Coord_Cell(unknown_slot19(0))];
}
