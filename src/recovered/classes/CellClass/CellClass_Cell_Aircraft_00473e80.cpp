// ObjectClass *CellClass::Cell_Aircraft(bool alt) const (0x00473E80): the aircraft in the
// cell (Find_Object kind 0x02).
#include "shared/cell.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958

ObjectClass *CellClass::Cell_Aircraft(bool alt) const
{
    return Find_Object(0x02, alt);
}
