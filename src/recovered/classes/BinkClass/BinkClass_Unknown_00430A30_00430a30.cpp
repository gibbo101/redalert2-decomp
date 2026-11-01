// void BinkClass::Unknown_00430A30(Surface *surface) (0x00430A30)
// Draws the companion's picture over the movie area of `surface`.
#include "shared/movie.hpp"

#pragma auto_inline(off)
void BinkClass::Unknown_00430A30(Surface *surface)
{
    if (Companion != 0 && Companion->unknown_00 != 0) {
        Rect &area = Companion->unknown_14;
        if (area.Is_Valid()) {
            Surface *source = Companion->unknown_10;
            Rect full = source->Get_Rect();
            Rect dest = area;
            dest.X += (Area.Width - full.Width) / 2;
            dest.Y += Area.Height - full.Height;
            dest.X += Area.X;
            dest.Y += Area.Y;
            surface->Copy_From(dest, *source, area, true, true);
        }
    }
}
#pragma auto_inline(on)
