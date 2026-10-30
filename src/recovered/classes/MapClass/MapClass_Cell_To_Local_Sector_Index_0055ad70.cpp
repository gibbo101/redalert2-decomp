// int MapClass::Cell_To_Local_Sector_Index(Cell const &cell) (0x0055AD70)
// The local view is a 3 x 3 grid of sectors along its diagonal rows: the
// sector (1-9) that holds a cell (TibSun Cell_To_Local_Sector_Index).
#include "shared/map.hpp"

int MapClass::Cell_To_Local_Sector_Index(Cell const &cell)
{
    int wrem = (2 * MapLocalSize.Width - 1) % 3;
    int wstep = (2 * MapLocalSize.Width - 1) / 3;
    int hrem = (2 * MapLocalSize.Height - 1) % 3;
    int hstep = (2 * MapLocalSize.Height - 1) / 3;

    int x = MapLocalSize.X + MapLocalSize.Y + 1;
    int y = MapSize.Width - MapLocalSize.X + MapLocalSize.Y;
    Cell origin = Cell(x, y);

    int column = (cell.X + (origin.Y - (wrem ? 1 : 0) - origin.X - cell.Y)) / wstep;
    int row = (cell.X + (cell.Y - (hrem ? 1 : 0) - origin.X - origin.Y)) / hstep;
    if (column == 3) {
        column = 2;
    }
    if (row == 3) {
        row = 2;
    }
    return column + 3 * row + 1;
}
