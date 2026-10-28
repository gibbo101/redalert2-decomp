// int TriColorGaugeClass::Draw_Me(int forced) (0x004D0730, slot 27)
// Redraws the box (raised when disabled) and fills it in up to three colours:
// up to the red limit, the yellow limit and the value. Several rectangles
// keep the original's mixed corner/size arithmetic.
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
#include "shared/text_print.hpp"
#include "shared/convert.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Draw_Me@GaugeClass@@UAEHH@Z=004d0280
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c

int TriColorGaugeClass::Draw_Me(int forced)
{
    if (GaugeClass::Draw_Me(forced)) {
        WWMouse->Conditional_Hide_Mouse(Rect(X, Y, Width, Height));
        Draw_Box(Rect(X, Y, Width, Height), IsDisabled ? 1 : 0, true);
        int red = Value_To_Pixel(RedLimit);
        int yellow = Value_To_Pixel(YellowLimit);
        int middle = Value_To_Pixel(CurValue);
        if (CurValue <= RedLimit) {
            if (IsHorizontal) {
                unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, middle - X + 1, Height - 2), unknown_drawer_8323c4->Convert(6));
            } else {
                unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, Width - 2, middle - Y + 1), unknown_drawer_8323c4->Convert(6));
            }
        } else if (CurValue > RedLimit && CurValue <= YellowLimit) {
            if (IsHorizontal) {
                unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, red - X + 1, Height - 2), unknown_drawer_8323c4->Convert(6));
                unknown_surface_83995c->Fill_Rect(Rect(red - X + 1, Y + 1, middle - X - 1, Height - 2), unknown_drawer_8323c4->Convert(5));
            } else {
                unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, Width - 2, red - Y + 1), unknown_drawer_8323c4->Convert(6));
                unknown_surface_83995c->Fill_Rect(Rect(X + 1, red - Y + 1, X + Width - 2, middle - Y + 1), unknown_drawer_8323c4->Convert(5));
            }
        } else if (CurValue > YellowLimit && CurValue <= MaxValue) {
            if (IsHorizontal) {
                unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, red - X + 1, Height - 2), unknown_drawer_8323c4->Convert(6));
                unknown_surface_83995c->Fill_Rect(Rect(red, Y + 1, yellow - X + 1, Height - 2), unknown_drawer_8323c4->Convert(5));
                unknown_surface_83995c->Fill_Rect(Rect(yellow, Y + 1, middle - X + 1, Height - 2), unknown_drawer_8323c4->Convert(3));
            } else {
                unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, Width - 2, red - Y + 1), unknown_drawer_8323c4->Convert(6));
                unknown_surface_83995c->Fill_Rect(Rect(X + 1, red, Width - 2, yellow - Y + 1), unknown_drawer_8323c4->Convert(5));
                unknown_surface_83995c->Fill_Rect(Rect(X + 1, yellow, Width - 2, middle - Y + 1), unknown_drawer_8323c4->Convert(3));
            }
        }
        if (HasThumb) {
            Draw_Thumb();
        }
        WWMouse->Conditional_Show_Mouse();
        return true;
    }
    return false;
}
