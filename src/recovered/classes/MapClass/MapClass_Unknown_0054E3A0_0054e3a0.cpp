// int MapClass::Unknown_0054E3A0(Cell const &cell, HouseClass *house) (0x0054E3A0)
// The house's +0x56D0 value for the 4 x 4 block of a cell (taken from the
// map's cell object, so off-map cells use the dummy cell's coordinates).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/house_screen.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

int MapClass::Unknown_0054E3A0(Cell const &cell, HouseClass *house)
{
    Cell coords = Map[cell].MapCoords;
    return house->unknown_56d0[Unknown_0054E370(coords)];
}
