// bool XSurface::Fill(int color) (0x00774E20, slot 6)
// Fills the whole surface.
#include "shared/surface.hpp"

bool XSurface::Fill(int color)
{
    return Fill_Rect(Get_Rect(), Get_Rect(), color);
}
