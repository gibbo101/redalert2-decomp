// bool DSurface::Copy_From(Rect const &toarea, Surface &source, Rect const &fromarea, bool trans, bool unknown) (0x004AAF80, slot 2)
// Copies fromarea of source to toarea, both clipped to their surfaces.
#include "shared/dsurface.hpp"

bool DSurface::Copy_From(Rect const &toarea, Surface &source, Rect const &fromarea, bool trans, bool unknown)
{
    return Copy_From(Get_Rect(), toarea, source, source.Get_Rect(), fromarea, trans, unknown);
}
