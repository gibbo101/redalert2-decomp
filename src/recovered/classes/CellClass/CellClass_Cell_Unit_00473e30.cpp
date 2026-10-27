// ObjectClass *CellClass::Cell_Unit(bool alt) const (0x00473E30): the unit in the
// cell (Find_Object kind 0x01).
#include "shared/cell.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958

ObjectClass *CellClass::Cell_Unit(bool alt) const
{
    return Find_Object(0x01, alt);
}
