// bool MapClass::Unknown_0055A590(Rect const &rect, bool flag) (0x0055A590)
// TibSun In_Local_Radar(Rect) shape: whether all four corner cells of a cell rectangle pass
// 0x0055A660; the corners are summed in 32 bits and narrowed by the Cell(int, int) constructor.
#include "shared/map.hpp"

bool MapClass::Unknown_0055A590(Rect const &rect, bool flag)
{
    return(Unknown_0055A660(Cell(rect.X, rect.Y), flag) &&
        Unknown_0055A660(Cell(rect.X + rect.Width - 1, rect.Y), flag) &&
        Unknown_0055A660(Cell(rect.X, rect.Y + rect.Height - 1), flag) &&
        Unknown_0055A660(Cell(rect.X + rect.Width - 1, rect.Y + rect.Height - 1), flag) ? 1 : 0);
}
