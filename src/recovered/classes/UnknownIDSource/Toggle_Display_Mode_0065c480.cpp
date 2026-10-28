// void __fastcall Toggle_Display_Mode_0065c480(bool preferred) (0x0065C480)
// With [Video] AllowModeToggle, switches to the RA2.INI screen size (when
// preferred and not already in it) or back to 640 x 480 (640 x 400 first)
// from a larger mode.
// @ref ?unknown_int_83964c@@3HA=0083964c
// @ref ?Set_Video_Mode_005434e0@@YI_NHH@Z=005434e0
// @ref ??_C@_0CA@GDJN@Toggle?5display?5mode?5to?5?$CFd?5X?5?$CFd?6?$AA@=007f1e18
// @ref ??_C@_0CP@HLKF@Toggling?5display?5mode?5back?5to?564@=007f1ed4
#include "shared/options.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/debug_printf.hpp"

void __fastcall Toggle_Display_Mode_0065c480(bool preferred)
{
    if (!unknown_allow_mode_toggle_a40d0b) {
        return;
    }
    if (preferred) {
        if (unknown_int_839648 != Options.ScreenWidth || unknown_int_83964c != Options.ScreenHeight) {
            Debug_Printf("Toggle display mode to %d X %d\n", Options.ScreenWidth, Options.ScreenHeight);
            Set_Video_Mode_005434e0(Options.ScreenWidth, Options.ScreenHeight);
        }
    } else if (unknown_int_839648 != 640 && unknown_int_83964c > 480) {
        Debug_Printf("Toggling display mode back to 640 X 480 / 400\n");
        if (!Set_Video_Mode_005434e0(640, 400)) {
            Set_Video_Mode_005434e0(640, 480);
        }
    }
}
