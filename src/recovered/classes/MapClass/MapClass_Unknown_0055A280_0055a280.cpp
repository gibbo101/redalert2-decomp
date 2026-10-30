// int MapClass::Unknown_0055A280(CoordStruct const &coord) (0x0055A280)
// The ground height at a lepton coordinate (TibSun Get_Height_GL): the global
// Map's cell under it, asked for the height at the coordinate's X and Y. The
// original copies the coordinate's first two dwords into the Point2D it
// passes (an 8-byte struct copy, Y read again for the cell index).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"

int MapClass::Unknown_0055A280(CoordStruct const &coord)
{
    Point2D point = *(Point2D const *)&coord;
    return Map[coord].unknown_4706c0(point);
}
