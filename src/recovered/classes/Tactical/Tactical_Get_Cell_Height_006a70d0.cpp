// int Tactical::Get_Cell_Height(CoordStruct const &coord) (0x006A70D0): the height
// of the ground under a coordinate, asked of its cell (TibSun
// Tactical::Get_Cell_Height).
#include "shared/tactical.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"

int Tactical::Get_Cell_Height(CoordStruct const &coord)
{
    CellClass *cellptr = &Map[coord];
    return cellptr->unknown_4706c0(Point2D(coord.X, coord.Y));
}
