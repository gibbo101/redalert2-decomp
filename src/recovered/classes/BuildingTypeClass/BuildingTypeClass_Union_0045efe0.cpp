// Rect __fastcall Union(Rect const &rect1, Rect const &rect2) (0x0045EFE0)
// The smallest rectangle holding both valid rectangles; an invalid one
// yields the other (Westwood's wwlib Union).
#include "shared/building_type.hpp"

Rect __fastcall Union(Rect const &rect1, Rect const &rect2);

Rect __fastcall Union(Rect const &rect1, Rect const &rect2)
{
    if (rect1.Is_Valid()) {
        if (rect2.Is_Valid()) {
            Rect r = rect1;
            if (r.X > rect2.X) {
                r.Width += r.X - rect2.X;
                r.X = rect2.X;
            }
            if (r.Y > rect2.Y) {
                r.Height += r.Y - rect2.Y;
                r.Y = rect2.Y;
            }
            if (r.X + r.Width < rect2.X + rect2.Width) {
                r.Width = rect2.X - r.X + rect2.Width + 1;
            }
            if (r.Y + r.Height < rect2.Y + rect2.Height) {
                r.Height = rect2.Y + rect2.Height - r.Y + 1;
            }
            return r;
        }
        return rect1;
    }
    return rect2;
}
