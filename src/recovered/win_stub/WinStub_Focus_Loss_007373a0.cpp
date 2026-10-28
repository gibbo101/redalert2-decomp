// void Focus_Loss() (0x007373A0)
// The game window lost the focus: pauses the radar movie, remembers whether the mouse was captured
// and releases it. The window procedure expands this copy (it is never called).
#include "shared/win_stub.hpp"
#include "shared/debug_printf.hpp"
#include "shared/mouse.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?Unknown_00406F50@@YAXXZ=00406f50
// @ref ?unknown_mouse_captured_b263e8@@3_NA=00b263e8
// @ref ??_C@_0CD@PHED@Focus_Loss?$CI?$CJ?3?5_MouseCaptured?5?$DN?5?$CF@=007fd0e4
// @ref ??_C@_0O@GJFN@Focus_Loss?$CI?$CJ?6?$AA@=007fd108
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0

void Focus_Loss()
{
    Debug_Printf("Focus_Loss()\n");
    Pause_Radar_Movie_005a0a90(true);
    Unknown_00406F50();
    if (WWMouse != 0) {
        unknown_mouse_captured_b263e8 = WWMouse->Is_Captured();
        Debug_Printf("Focus_Loss(): _MouseCaptured = %s\n", unknown_mouse_captured_b263e8 ? "true" : "false");
        WWMouse->Release_Mouse();
    }
}
