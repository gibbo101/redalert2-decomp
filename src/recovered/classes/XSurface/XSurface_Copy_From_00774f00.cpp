// bool XSurface::Copy_From(Rect const &toarea, Surface &source, Rect const &fromarea, bool trans, bool unknown) (0x00774F00, slot 2)
// Copies fromarea of source to toarea, both clipped to their surfaces: the
// seven-argument copy (slot 3) with the two surfaces' rectangles as windows.
// VC6 expands the seven-argument copy (0x00775060, defined later in the
// unit) and its blitter helpers inline here.
#include "shared/surface.hpp"

bool XSurface::Copy_From(Rect const &toarea, Surface &source, Rect const &fromarea, bool trans, bool unknown)
{
    return XSurface::Copy_From(Get_Rect(), toarea, source, source.Get_Rect(), fromarea, trans, unknown);
}
