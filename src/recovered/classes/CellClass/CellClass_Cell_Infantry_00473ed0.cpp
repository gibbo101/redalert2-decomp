// ObjectClass *CellClass::Cell_Infantry(bool alt) const (0x00473ED0): the infantry in the
// cell (Find_Object kind 0x0F).
#include "shared/cell.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958

ObjectClass *CellClass::Cell_Infantry(bool alt) const
{
    return Find_Object(0x0F, alt);
}
