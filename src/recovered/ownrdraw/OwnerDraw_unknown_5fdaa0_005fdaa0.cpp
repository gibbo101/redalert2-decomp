// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
#include "shared/win32_api.hpp"
#include "shared/hicolor.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// A screen pixel as a palette-relative Win32 colour (PALETTERGB: 0x02BBGGRR).
unsigned long __fastcall unknown_5fdaa0(unsigned short pixel)
{
    RGBClass color = Unpack_Hicolor_Pixel(pixel);
    return 0x02000000 | ((unsigned long)color.Blue << 16) | ((unsigned short)color.Green << 8) | color.Red;
}

}
