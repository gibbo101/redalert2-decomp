// Cell MapClass::Clip_To_Map(Cell const &cell) (0x00568D60)
// A cell moved inside the local view (TibSun Clip_To_Map): first onto the
// view's diagonal band, then along the diagonal until 0x0055A660 accepts it
// (the cell's +0x11B height, one more on a slope +0x11C, offsets the test).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"

Cell MapClass::Clip_To_Map(Cell const &cell)
{
    int x = cell.X;
    int y = cell.Y;

    if (x - y >= 2 * (MapLocalSize.X + MapLocalSize.Width) - MapSize.Width) {
        int delta = x + MapSize.Width + 2 * (1 - MapLocalSize.X - MapLocalSize.Width) - y;
        x -= delta / 2;
        y += delta / 2;
    } else if (y - x >= MapSize.Width - 2 * MapLocalSize.X) {
        int delta = y + 2 * MapLocalSize.X + 2 - MapSize.Width - x;
        y -= delta / 2;
        x += delta / 2;
    }

    CellClass *cellptr = &Map[Cell(x, y)];
    int height = cellptr->unknown_11b;
    int slope = cellptr->unknown_11c;
    if (slope != 0) {
        if (x + y < height + MapSize.Width + 2 * MapLocalSize.Y + 4) {
            height++;
        }
    }

    if (x + y <= height + MapSize.Width + 2 * MapLocalSize.Y) {
        do {
            x++;
            y++;
        } while (!Unknown_0055A660(Cell(x, y), true));
    } else if (x + y > height + MapSize.Width + 2 * (MapLocalSize.Y + MapLocalSize.Height) + 2) {
        do {
            x--;
            y--;
        } while (!Unknown_0055A660(Cell(x, y), true));
    }
    return Cell(x, y);
}
