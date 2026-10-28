// int GaugeClass::Draw_Me(int forced) (0x004D0280, slot 27)
// A box; a colorized gauge fills it up to the value in the gadget colour
// scheme's colour; then the thumb.
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
#include "shared/text_print.hpp"
#include "shared/color_scheme.hpp"
#include "shared/convert.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Draw_Me@ControlClass@@UAEHH@Z=00483530
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0
// @ref ?Gadget_Color_Scheme@@YAHXZ=004cefc0
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c

int GaugeClass::Draw_Me(int forced)
{
    if (ControlClass::Draw_Me(forced)) {
        WWMouse->Conditional_Hide_Mouse(Rect(X, Y, Width, Height));
        Draw_Box(Rect(X, Y, Width, Height), 0, true);
        if (IsColorized) {
            int middle = Value_To_Pixel(CurValue);
            int color = ColorSchemes[Gadget_Color_Scheme()]->unknown_color_0x330;
            if (IsHorizontal) {
                if (middle >= X + 1) {
                    unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, middle - X - 1, Height - 2), unknown_drawer_8323c4->Convert(color));
                }
            } else {
                if (middle >= Y + 1) {
                    unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, Width - 2, middle - Y - 1), unknown_drawer_8323c4->Convert(color));
                }
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
