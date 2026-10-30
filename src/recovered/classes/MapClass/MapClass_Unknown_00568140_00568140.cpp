// bool MapClass::Unknown_00568140(CoordStruct const &coord) (0x00568140)
// Whether a lepton position is shrouded (TibSun Is_Shrouded): the cell its
// height level projects onto (half a cell per level up and left) is not
// mapped (+0x12C bit 3); on an odd level both that cell and its facing-3
// neighbour must be unmapped.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"

bool MapClass::Unknown_00568140(CoordStruct const &coord)
{
    int level = coord.Z / unknown_geometry_g;
    if ((level & 1) != 0) {
        int offset = level / 2 + 1;
        Cell cell = Cell(coord.X / 256, coord.Y / 256);
        CellClass *cellptr = &Map[Cell(cell.X - offset, cell.Y - offset)];
        if (cellptr->unknown_12c & 8) {
            return false;
        }
        cellptr = &cellptr->Adjacent_Cell(3);
        if (!(cellptr->unknown_12c & 8)) {
            return true;
        }
    } else {
        int offset = level / 2;
        Cell cell = Cell(coord.X / 256, coord.Y / 256);
        CellClass *cellptr = &Map[Cell(cell.X - offset, cell.Y - offset)];
        if (!(cellptr->unknown_12c & 8)) {
            return true;
        }
    }
    return false;
}
