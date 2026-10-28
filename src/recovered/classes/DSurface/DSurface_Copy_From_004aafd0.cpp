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

// Intersect (kept copy 0x0041FDF0) is an inline header function in the
// original: Copy_From expands it for both windows (the second expansion makes
// its zero rectangle with the out-of-line Rect constructor 0x0042BCD0), while
// Fill_Rect, Fill_Rect_Trans and Draw_Gradient_Line later in this unit call
// it out of line. Defined here (the unit's first user) until shared/rect.hpp
// carries it, as in the BinkClass, MSAnim and ObjectClass units.
inline Rect __fastcall Intersect(Rect const &rect1, Rect const &rect2, int *x, int *y)
{
    Rect empty(0, 0, 0, 0);
    Rect result = rect2;
    if (!rect1.Is_Valid() || !rect2.Is_Valid()) {
        return empty;
    }
    if (result.X < rect1.X) {
        result.Width += result.X - rect1.X;
        result.X = rect1.X;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y < rect1.Y) {
        result.Height += result.Y - rect1.Y;
        result.Y = rect1.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (result.X + result.Width > rect1.X + rect1.Width) {
        result.Width = rect1.X - result.X + rect1.Width;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y + result.Height > rect1.Y + rect1.Height) {
        result.Height = rect1.Y + rect1.Height - result.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (x != 0) {
        *x += rect2.X - result.X;
    }
    if (y != 0) {
        *y += rect2.Y - result.Y;
    }
    return result;
}

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
