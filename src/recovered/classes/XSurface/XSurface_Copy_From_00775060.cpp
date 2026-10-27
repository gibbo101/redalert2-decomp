// bool XSurface::Copy_From(Rect const &toclip, Rect const &toarea, Surface &source, Rect const &fromclip, Rect const &fromarea, bool trans, bool unknown) (0x00775060, slot 3)
// Copies fromarea of source to toarea, clipped to fromclip and toclip, with
// the plain or transparent blitter for the surface's pixel size.
#include "shared/blitter.hpp"
#include "shared/surface.hpp"
// @ref ?Clip_Blit_Rects@@YI_NAAVRect@@ABV1@01@Z=00775190

bool XSurface::Copy_From(Rect const &toclip, Rect const &toarea, Surface &source, Rect const &fromclip,
                         Rect const &fromarea, bool trans, bool unknown)
{
    Rect torect = toarea;
    Rect fromrect = fromarea;
    if (Clip_Blit_Rects(torect, toclip, fromrect, fromclip)) {
        if (trans) {
            return Bit_Blit_Trans(*this, torect, source, fromrect);
        }
        return Bit_Blit_Plain(*this, torect, source, fromrect);
    }
    return false;
}
