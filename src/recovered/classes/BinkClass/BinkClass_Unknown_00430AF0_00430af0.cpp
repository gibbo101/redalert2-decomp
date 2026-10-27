// void BinkClass::Unknown_00430AF0(Surface *surface) (0x00430AF0)
// Clears the companion's clear area (colour 0) within the movie area.
#include "shared/movie.hpp"

#pragma auto_inline(off)
void BinkClass::Unknown_00430AF0(Surface *surface)
{
    if (Companion != 0 && Companion->unknown_00 != 0) {
        Rect area = Companion->unknown_24;
        if (area.Is_Valid()) {
            Rect full = Companion->unknown_10->Get_Rect();
            area.X += (Area.Width - full.Width) / 2;
            area.Y += Area.Height - full.Height;
            area.X += Area.X;
            area.Y += Area.Y;
            surface->Fill_Rect(area, 0);
        }
    }
}
#pragma auto_inline(on)
