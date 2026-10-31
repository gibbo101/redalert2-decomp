// CellClass *MapClass::Get_Local_Grid_Cell(Cell const &cell, int spacing, bool unbiased) (0x0055AA80)
// The cell of a sampling grid of the given spacing over the local map
// (TibSun Get_Local_Grid_Cell): the cell moved up to the next grid line of
// each axis, measured from the local map's corner; unless unbiased, cells in
// the lower part of the local map step back half a spacing, or one less than
// a spacing near the bottom.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"

CellClass *MapClass::Get_Local_Grid_Cell(Cell const &cell, int spacing, bool unbiased)
{
    if (spacing == 1) {
        return &Map[cell];
    }

    int x = cell.X;
    int y = cell.Y;
    Cell local = XY_Cell(MapLocalSize.X + MapLocalSize.Y + 1, MapSize.Width - MapLocalSize.X + MapLocalSize.Y);
    int xx = (6000 * spacing + local.X - x) % spacing;
    int yy = (6000 * spacing + local.Y - y) % spacing;

    if (xx > 0) {
        x += spacing - xx;
    }
    if (yy > 0) {
        y += spacing - yy;
    }

    int dsum = local.X + local.Y;
    if (unbiased || (y + x < dsum + 2 * MapLocalSize.Height / 3)) {
        return &Map[Cell(x, y)];
    } else if (y + x < dsum + 4 * MapLocalSize.Height / 3 && spacing > 2) {
        return &Map[Cell(x, y) - Cell(spacing / 2, spacing / 2)];
    } else {
        return &Map[Cell(x, y) - Cell(spacing - 1, spacing - 1)];
    }
}
