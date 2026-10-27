// void *FootClass::unknown_slot26() (0x004CD650)
// The image to draw: the real type's (slot 50 with false) for an enemy unit
// the player sees through a cell not visible to him; the disguise's (slot
// 50 with true) when slot 245 refuses the player; otherwise ObjectClass's.
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/object_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_47c300@UnknownCellClass@@QAE_NH@Z=0047c300
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_slot26@ObjectClass@@UAEPAXXZ=005d27b0

void *FootClass::unknown_slot26()
{
    UnknownCellClass *cell = (UnknownCellClass *)&Map[Coord_Cell(Center_Coord())];
    if (!House->Is_Ally(unknown_player_a35db4) && unknown_slot48() && !cell->unknown_47c300(unknown_player_a35db4->ArrayIndex)) {
        return unknown_slot50(false)->unknown_a4;
    }
    if (!unknown_slot245(unknown_player_a35db4)) {
        return unknown_slot50(true)->unknown_a4;
    }
    return ObjectClass::unknown_slot26();
}
