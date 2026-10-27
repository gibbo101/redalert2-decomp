// void BuildingClass::unknown_slot58(CoordStruct const &coord) (0x0044EED0, slot 58)
// Sets the building occupation bit of the cell at coord (the ground level's
// +0x124).
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"

void BuildingClass::unknown_slot58(CoordStruct const &coord)
{
    Map_Cell_At(Coord_Cell(coord))->unknown_124.Occupy.Building = true;
}
