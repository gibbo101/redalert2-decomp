// int ShapeButtonClass::Draw_Me(int forced) (0x006751E0, slot 27)
// Draws the button's shape frame: 2 when disabled; with +0x40 set, the on
// state (plus 3 with +0x34 set); otherwise the pressed state.
#include "shared/gadget.hpp"
#include "shared/palette.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Draw_Me@ControlClass@@UAEHH@Z=00483530
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_window_839640@@3VRect@@A=00839640

int ShapeButtonClass::Draw_Me(int forced)
{
    if (ControlClass::Draw_Me(forced) && Shape) {
        int shapenum;
        if (IsDisabled) {
            shapenum = 2;
        } else if (unknown_40) {
            if (unknown_34) {
                shapenum = (IsOn ? 1 : 0) + 3;
            } else {
                shapenum = IsOn ? 1 : 0;
            }
        } else {
            shapenum = IsPressed ? 1 : 0;
        }
        Surface *surface = unknown_4c ? unknown_surface_839948 : unknown_surface_83995c;
        CC_Draw_Shape(surface, (ConvertClass *)unknown_50, (ShapeFileStruct const *)Shape, shapenum,
                      Point2D(X + OffsetX, Y + OffsetY), unknown_window_839640, unknown_55 ? 0x800 : 0,
                      0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        unknown_54 = true;
        return true;
    }
    return false;
}
