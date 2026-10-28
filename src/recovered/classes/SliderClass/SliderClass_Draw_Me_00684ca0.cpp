// int SliderClass::Draw_Me(int forced) (0x00684CA0, slot 27)
#include "shared/gadget.hpp"
#include "shared/rect.hpp"
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0

int SliderClass::Draw_Me(int forced)
{
    if (NoButtons && ControlClass::Draw_Me(forced)) {
        Draw_Box(Rect(X, Y, Width, Height), 0, true);
        Draw_Thumb();
        return true;
    }
    return GaugeClass::Draw_Me(forced);
}
