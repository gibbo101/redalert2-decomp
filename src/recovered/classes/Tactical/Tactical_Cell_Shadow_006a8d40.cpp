// int Tactical::Cell_Shadow(Cell const &cell, bool fog) (0x006A8D40): the shroud (or, with fog, the fog)
// edge frame of a cell from which of its eight neighbours are unrevealed: -2 for solid black, -1 for none
// (TibSun Tactical::Cell_Shadow).
#include "shared/tactical.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_shadow_7ac3bc@@3QBDB=007ac3bc

// The edge frame of each neighbour mask (0x007AC3BC; TibSun Cell_Shadow's _shadow table).
extern char const unknown_shadow_7ac3bc[256];

int Tactical::Cell_Shadow(Cell const &cell, bool fog)
{
    int index = 0;
    int value = -1;

    CellClass const *cellptr = &Map[cell];

    if (fog) {
        if (!(cellptr->unknown_140 & 3)) value = -2;

        if (cellptr->unknown_140 & 2) {
            Cell c;
            c = Cell(cell.X - 1, cell.Y - 1);
            if (!(Map[c].unknown_140 & 2)) index |= 0x40;
            c = Cell(cell.X, cell.Y - 1);
            if (!(Map[c].unknown_140 & 2)) index |= 0x80;
            c = Cell(cell.X + 1, cell.Y - 1);
            if (!(Map[c].unknown_140 & 2)) index |= 0x01;
            c = Cell(cell.X - 1, cell.Y);
            if (!(Map[c].unknown_140 & 2)) index |= 0x20;
            c = Cell(cell.X + 1, cell.Y);
            if (!(Map[c].unknown_140 & 2)) index |= 0x02;
            c = Cell(cell.X - 1, cell.Y + 1);
            if (!(Map[c].unknown_140 & 2)) index |= 0x10;
            c = Cell(cell.X, cell.Y + 1);
            if (!(Map[c].unknown_140 & 2)) index |= 0x08;
            c = Cell(cell.X + 1, cell.Y + 1);
            if (!(Map[c].unknown_140 & 2)) index |= 0x04;

            value = unknown_shadow_7ac3bc[index];
        }
    } else {
        if (!(cellptr->unknown_12c & 0x18)) value = -2;

        if (cellptr->unknown_12c & 8) {
            Cell c;
            c = Cell(cell.X - 1, cell.Y - 1);
            if (!(Map[c].unknown_12c & 8)) index |= 0x40;
            c = Cell(cell.X, cell.Y - 1);
            if (!(Map[c].unknown_12c & 8)) index |= 0x80;
            c = Cell(cell.X + 1, cell.Y - 1);
            if (!(Map[c].unknown_12c & 8)) index |= 0x01;
            c = Cell(cell.X - 1, cell.Y);
            if (!(Map[c].unknown_12c & 8)) index |= 0x20;
            c = Cell(cell.X + 1, cell.Y);
            if (!(Map[c].unknown_12c & 8)) index |= 0x02;
            c = Cell(cell.X - 1, cell.Y + 1);
            if (!(Map[c].unknown_12c & 8)) index |= 0x10;
            c = Cell(cell.X, cell.Y + 1);
            if (!(Map[c].unknown_12c & 8)) index |= 0x08;
            c = Cell(cell.X + 1, cell.Y + 1);
            if (!(Map[c].unknown_12c & 8)) index |= 0x04;

            value = unknown_shadow_7ac3bc[index];
        }
    }
    return value;
}
