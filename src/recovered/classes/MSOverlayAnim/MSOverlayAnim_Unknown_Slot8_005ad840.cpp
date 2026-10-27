// void MSOverlayAnim::Unknown_Slot8(int unknown1) (0x005AD840, slot 8)
// Draws the current frame into the background surface at its fade level
// (while active).
#include "shared/ms_anim.hpp"
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?unknown_fade_flags_7e57f0@@3PAHA=007e57f0

void MSOverlayAnim::Unknown_Slot8(int unknown1)
{
    unsigned level = (unsigned)unknown_40 < 3 ? unknown_40 : 3;
    if (unknown_0C) {
        CC_Draw_Shape(unknown_surface_839958, Drawer, Shape, Frame, Point2D(X, Y), unknown_surface_839958->Get_Rect(),
                      unknown_fade_flags_7e57f0[level] | Flags, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    }
}
