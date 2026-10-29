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

// A Win32 colour (0x00BBGGRR) as a screen pixel; -1 stays -1.
int __fastcall unknown_5fda40(unsigned long color)
{
    if (color == 0xffffffff) {
        return -1;
    }
    return ((int)(color & 0xff) >> unknown_shift_852fbc << unknown_shift_852fb8)
         | ((color >> 8 & 0xff) >> unknown_shift_852fcc << unknown_shift_852fc8)
         | ((color >> 16 & 0xff) >> unknown_shift_852fc4 << unknown_shift_852fc0);
}

}
