// Fill through DirectDraw when available and idle, otherwise use the software surface fill.
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"
#include "shared/win32_api.hpp"
// @ref ?unknown_flag_7d6294@@3_NA=007d6294
// @ref ?Fill_Rect@XSurface@@UAE_NABVRect@@0H@Z=007743c0
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0

inline Rect Offset_Fill_Rect(Rect const &window, Rect const &area) {
    Point2D origin(window.X, window.Y);
    Point2D offset(area.X, area.Y);
    Point2D position(origin.X + offset.X, offset.Y + origin.Y);
    return Rect(position.X, position.Y, area.Width, area.Height);
}
bool DSurface::Fill_Rect(Rect const &cliprect, Rect const &fillrect, int color)
{
    RECT rectangle;
    if (VideoSurfacePtr != 0 && fillrect.Is_Valid()) {
        if (unknown_flag_7d6294 && !Is_Locked() && VideoSurfacePtr->GetBltStatus(DDGBS_CANBLT) == DD_OK) {
            if (!Restore_Lost_Surface()) return false;
            Rect clipped = cliprect.Intersect(Get_Rect());
            Rect area = Offset_Fill_Rect(cliprect, fillrect);
            area = area.Intersect(clipped);
            if (area.Is_Valid()) {
                rectangle.left = area.X;
                rectangle.top = area.Y;
                rectangle.right = area.X + area.Width;
                rectangle.bottom = area.Y + area.Height;
                DDBLTFX effects;
                memset(&effects, 0, sizeof(effects));
                effects.dwSize = sizeof(effects);
                effects.dwFillColor = color;
                return VideoSurfacePtr->Blt(&rectangle, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &effects) == DD_OK;
            }
            return false;
        }
        return XSurface::Fill_Rect(cliprect, fillrect, color);
    }
    return false;
}
