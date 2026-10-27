// Cell DisplayClass::Unknown_00499810(Cell const *list) (0x00499810)
// The size of a cell list (offsets ending with 0x7FFF, 0x7FFF): its extent
// in x and y, at least one cell each; 0 x 0 when there is no list.
#include "shared/display.hpp"

Cell DisplayClass::Unknown_00499810(Cell const *list)
{
    int min_x = 512;
    int max_x = -512;
    int min_y = 512;
    int max_y = -512;
    Cell size(0, 0);
    if (list) {
        while (list->X != 0x7FFF || list->Y != 0x7FFF) {
            int x = list->X;
            int y = list->Y;
            if (max_x <= x) {
                max_x = x;
            }
            if (min_x >= x) {
                min_x = x;
            }
            if (max_y <= y) {
                max_y = y;
            }
            if (min_y >= y) {
                min_y = y;
            }
            list++;
        }
        size.X = (short)(max_x - min_x + 1 < 1 ? 1 : max_x - min_x + 1);
        size.Y = (short)(max_y - min_y + 1 < 1 ? 1 : max_y - min_y + 1);
    }
    return size;
}
