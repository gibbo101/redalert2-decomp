// Cell Tactical::Coord_To_Cell(CoordStruct const &coord) (0x006A6A50): the cell
// drawn over a coordinate: from six cells down the view diagonal, steps back 8
// leptons at a time until a cell, lowered by its height difference to the
// coordinate's cell (plus four levels under a bridge when that cell is a
// bridge surface), lies at or before the cell (TibSun Tactical::Coord_To_Cell).
#include "shared/tactical.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

Cell Tactical::Coord_To_Cell(CoordStruct const &coord)
{
    Cell cell = Coord_Cell(coord);
    CoordStruct center = Cell_Coord(cell);

    bool isbridge = (Map[cell].unknown_140 >> 12) & 1;
    int baseheight = Map[cell].unknown_11b;

    CoordStruct scan = CoordStruct(center.X + 256 * 6, center.Y + 256 * 6, 0);

    Cell scancell = cell;
    while (true) {
        scan -= CoordStruct(8, 8, 0);
        scancell = Coord_Cell(scan);

        CellClass *cellptr = &Map[scancell];
        int heightdiff = cellptr->unknown_11b - baseheight;
        if (isbridge) {
            heightdiff += 4 * ((cellptr->unknown_140 >> 8) & 1);
        }

        Cell projected = Coord_Cell(scan - CoordStruct(heightdiff * 128, heightdiff * 128, 0));
        if (projected.X <= cell.X && projected.Y <= cell.Y) {
            return scancell;
        }
        if (scancell == cell) {
            return cell;
        }
    }
}
