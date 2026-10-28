// Copy fromarea of source (inside fromclip) to toarea of this surface (inside
// toclip) with a DirectDraw blit when both are DirectDraw surfaces of the same
// pixel size; the software copy handles transparent, locked or mismatched
// sources and same-size copies that DirectDraw would do in system memory.
#include "shared/dsurface.hpp"
#include "shared/win32_api.hpp"
// @ref ?Copy_From@XSurface@@UAE_NABVRect@@AAVSurface@@0_N2@Z=00774f00
// @ref ?Clip_Blit_Rects@@YI_NAAVRect@@ABV1@01@Z=00775190
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0
#include "shared/rect_intersect.hpp"

bool DSurface::Copy_From(Rect const &toclip, Rect const &toarea, Surface &source,
                         Rect const &fromclip, Rect const &fromarea, bool trans, bool unknown)
{
    if (toclip.Width <= 0 || toclip.Height <= 0 || fromclip.Width <= 0 || fromclip.Height <= 0
        || toarea.Width <= 0 || toarea.Height <= 0 || fromarea.Width <= 0 || fromarea.Height <= 0) {
        return false;
    }
    bool software = false;
    if (!source.Is_Direct_Draw() || source.Is_Locked() == true || trans == true
        || Bytes_Per_Pixel() != source.Bytes_Per_Pixel()) {
        software = true;
    }
    bool system_copy = (IsPrimary == true && unknown_flag_851cb0 == true) ? false : unknown;
    if (!software && system_copy == true) {
        if (!IsVideoRam || (source.Is_Direct_Draw() == true && !((DSurface &)source).IsVideoRam)) {
            if (fromarea.Width == toarea.Width && fromarea.Height == toarea.Height) {
                software = true;
            }
        }
    }
    if (!Restore_Lost_Surface()) {
        return false;
    }
    if (software == true) {
        return XSurface::Copy_From(toarea, source, fromarea, trans, true);
    }
    Rect destination_area = toarea;
    Rect source_area = fromarea;
    Rect source_window = fromclip.Intersect(source.Get_Rect());
    Rect destination_window = toclip.Intersect(Get_Rect());
    if (Clip_Blit_Rects(destination_area, destination_window, source_area, source_window)) {
        RECT destination_rectangle;
        destination_rectangle.left = destination_area.X + destination_window.X;
        destination_rectangle.top = destination_area.Y + destination_window.Y;
        destination_rectangle.right = destination_area.X + destination_window.X + destination_area.Width;
        destination_rectangle.bottom = destination_area.Y + destination_window.Y + destination_area.Height;
        RECT source_rectangle;
        source_rectangle.left = source_area.X + source_window.X;
        source_rectangle.top = source_area.Y + source_window.Y;
        source_rectangle.right = source_area.X + source_window.X + source_area.Width;
        source_rectangle.bottom = source_area.Y + source_window.Y + source_area.Height;
        return VideoSurfacePtr->Blt(&destination_rectangle, ((DSurface &)source).VideoSurfacePtr,
                                    &source_rectangle, DDBLT_WAIT, 0) == DD_OK;
    }
    return false;
}
