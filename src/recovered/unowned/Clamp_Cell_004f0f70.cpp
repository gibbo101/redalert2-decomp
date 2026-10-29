// Cell Clamp_Cell_004F0F70(Rect const &rect, Cell const &cell) (0x004F0F70)
// The cell moved inside the cell rectangle (each coordinate clamped to
// [X, X + Width - 1]). No caller; name, convention and owner are hypotheses.
#include "shared/house.hpp"
#include "shared/rect.hpp"

Cell __fastcall Clamp_Cell_004F0F70(Rect const &rect, Cell const &cell)
{
    Cell result = cell;
    if (result.X < rect.X) result.X = rect.X;
    if (result.X >= rect.X + rect.Width) result.X = rect.X + rect.Width - 1;
    if (result.Y < rect.Y) result.Y = rect.Y;
    if (result.Y >= rect.Y + rect.Height) result.Y = rect.Y + rect.Height - 1;
    return result;
}
