// ObjectClass *CellClass::Cell_Terrain(bool alt) const (0x004717E0): the terrain object in the
// cell (Find_Object kind 0x24).
#include "shared/cell.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958

ObjectClass *CellClass::Cell_Terrain(bool alt) const
{
    return Find_Object(0x24, alt);
}
