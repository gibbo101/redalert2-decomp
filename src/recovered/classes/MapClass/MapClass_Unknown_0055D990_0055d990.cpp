// void MapClass::Unknown_0055D990(Cell const &cell) (0x0055D990)
// Reduces tiberium around a cell (TibSun Area_Reduce_Tiberium): for each
// offset within 5 cells (11 x 11 square, Cell_Length of the offset up to 5)
// the centre cell itself, as in the original, gives up one unit (CellClass
// 0x00475DB0).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/unknown_geometry.hpp"

// The length of a cell offset in cells, truncated to a short (TibSun Cell::Length;
// X squared first, unlike unknown_geometry.hpp's Cell_Length).
static inline short Offset_Length(Cell const &cell)
{
    return (short)unknown_sqrt_4ba410((double)cell.X * cell.X + (double)cell.Y * cell.Y);
}

void MapClass::Unknown_0055D990(Cell const &cell)
{
    for (int x = -5; x <= 5; x++) {
        for (int y = -5; y <= 5; y++) {
            Cell other = Cell(cell + Cell(x, y));
            Cell offset = cell - other;
            if (Offset_Length(offset) <= 5) {
                CellClass *cellptr = &Map[cell];
                if (cellptr != 0) {
                    cellptr->unknown_475db0(1);
                }
            }
        }
    }
}
