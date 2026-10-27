// int AircraftClass::unknown_slot182(AbstractClass *object, Cell *cell) (0x00418CF0, slot 182)
// Looks for a cell next to the aircraft (facings in table order) that is
// on the map and either object's cell or passes the cell's test
// (0x00478760); leaves it in *cell (the last one tried otherwise; the zero
// cell before the search). Always 0.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref _unknown_geometry_k=0083c478
// @ref ?unknown_facings_7ce4c8@@3QBHB=007ce4c8
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Unknown_00478760@CellClass@@QAE_NHHHHHHH@Z=00478760

int AircraftClass::unknown_slot182(AbstractClass *object, Cell *cell)
{
    *cell = unknown_geometry_k;
    Cell center = Coord_Cell(Center_Coord());
    for (int index = 0; index < 8; index++) {
        *cell = Adjacent_Cell(Cell(center), unknown_facings_7ce4c8[index]);
        if (Map.Unknown_0054AAB0(*cell)) {
            Cell here = Coord_Cell(object->Center_Coord());
            if (here.X == cell->X && here.Y == cell->Y) {
                break;
            }
            if (Map[*cell].Unknown_00478760(0, 0, 0, -1, 0, -1, 1)) {
                break;
            }
        }
    }
    return 0;
}
