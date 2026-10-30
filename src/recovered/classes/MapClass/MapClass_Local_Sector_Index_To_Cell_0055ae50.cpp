// Cell MapClass::Local_Sector_Index_To_Cell(int index) (0x0055AE50)
// The cell that stands for one sector (1-9) of the local view's 3 x 3 grid
// (the inverse of 0x0055AD70; TibSun Local_Sector_Index_To_Cell).
#include "shared/map.hpp"

Cell MapClass::Local_Sector_Index_To_Cell(int index)
{
    int wrem = (2 * MapLocalSize.Width - 1) % 3;
    int wstep = (2 * MapLocalSize.Width - 1) / 3;
    int hrem = (2 * MapLocalSize.Height - 1) % 3;
    int hstep = (2 * MapLocalSize.Height - 1) / 3;

    int column = (index - 1) % 3;
    int row = (index - 1) / 3;

    int x = MapLocalSize.X + MapLocalSize.Y + 1;
    int y = MapSize.Width - MapLocalSize.X + MapLocalSize.Y;

    int left = (wrem ? 1 : 0) + column * wstep;
    int top = (hrem ? 1 : 0) + row * hstep;
    int right = left + ((left & 1) ? 1 : 0);
    int bottom = top + ((top & 1) ? 1 : 0);

    int cx = (bottom + right) / 2;
    int cy = (top - left) / 2;
    return Cell(cx, cy) + Cell(x, y);
}
