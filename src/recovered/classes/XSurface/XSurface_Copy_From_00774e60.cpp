// bool XSurface::Copy_From(Surface &source, bool trans, bool unknown) (0x00774E60, slot 1)
// Copies the whole source surface to the top left corner.
#include "shared/surface.hpp"

bool XSurface::Copy_From(Surface &source, bool trans, bool unknown)
{
    Rect torect = Get_Rect();
    torect.X = 0;
    torect.Y = 0;
    Rect fromrect = source.Get_Rect();
    fromrect.X = 0;
    fromrect.Y = 0;
    return Copy_From(torect, source, fromrect, trans, unknown);
}
