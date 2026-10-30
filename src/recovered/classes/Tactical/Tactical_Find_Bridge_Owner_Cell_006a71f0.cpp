// CellClass *Tactical::Find_Bridge_Owner_Cell(Cell const &cell) (0x006A71F0): the
// bridge deck cell (+0x140 bit 0x80, an overlay) whose span covers the cell:
// east-west decks (bit 0x800) two and one cells east, scanning five cells
// south, then north-south decks two and one cells south, scanning east (TibSun
// Tactical::Find_Bridge_Owner_Cell; nothing calls it).
#include "shared/tactical.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

CellClass *Tactical::Find_Bridge_Owner_Cell(Cell const &cell)
{
    CellClass *cellptr;
    Cell scan;
    int i;

    scan = cell + Cell(2, 0);
    for (i = 0; i < 5; ++i) {
        cellptr = &Map[scan];
        if ((cellptr->unknown_140 & 0x80) && cellptr->OverlayIndex && (cellptr->unknown_140 & 0x800)) {
            return cellptr;
        }
        scan.Y++;
    }

    scan = cell + Cell(1, 0);
    for (i = 0; i < 5; ++i) {
        cellptr = &Map[scan];
        if ((cellptr->unknown_140 & 0x80) && cellptr->OverlayIndex && (cellptr->unknown_140 & 0x800)) {
            return cellptr;
        }
        scan.Y++;
    }

    scan = cell + Cell(0, 2);
    for (i = 0; i < 5; ++i) {
        cellptr = &Map[scan];
        if ((cellptr->unknown_140 & 0x80) && cellptr->OverlayIndex && !(cellptr->unknown_140 & 0x800)) {
            return cellptr;
        }
        scan.X++;
    }

    scan = cell + Cell(0, 1);
    for (i = 0; i < 5; ++i) {
        cellptr = &Map[scan];
        if ((cellptr->unknown_140 & 0x80) && cellptr->OverlayIndex && !(cellptr->unknown_140 & 0x800)) {
            return cellptr;
        }
        scan.X++;
    }

    return 0;
}
