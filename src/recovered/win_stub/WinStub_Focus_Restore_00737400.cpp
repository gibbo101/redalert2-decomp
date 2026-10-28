// void Focus_Restore() (0x00737400)
// The game window regained the focus: re-captures the mouse when it was captured on the loss, restores
// the lost surfaces (clearing them to black unless the first frames after a restart), flags the map for
// a complete redraw, invalidates the window, resumes the radar movie and re-activates the current
// dialog window. Like Focus_Loss, an out-of-line copy of what the window procedure expands.
// @ref ??_C@_0BB@LBMH@Focus_Restore?$CI?$CJ?6?$AA@=007fd140
// @ref ??_C@_0CG@NEFH@Focus_Restore?$CI?$CJ?3?5_MouseCaptured?5@=007fd118
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ?Unknown_00406F70@@YAXXZ=00406f70
// @ref ?unknown_mouse_captured_b263e8@@3_NA=00b263e8
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?unknown_flag_a40d04@@3_NA=00a40d04
// @ref ?unknown_flag_851cb0@@3_NA=00851cb0
// @ref ?unknown_flag_8373c3@@3_NA=008373c3
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_surface_839944@@3PAVSurface@@A=00839944
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839954@@3PAVDSurface@@A=00839954
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?unknown_surface_839964@@3PAVSurface@@A=00839964
// @ref ?unknown_window_839640@@3VRect@@A=00839640
// @ref ?Restore_Check@DSurface@@QAE_NXZ=004aaf00
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Pause_Radar_Movie_005a0a90@@YIX_N@Z=005a0a90
// @ref ?Unknown_00735B10@@YAPAUHWND__@@XZ=00735b10
// @ref __imp__InvalidateRect@12=0079a494
// @ref __imp__SetActiveWindow@4=0079a420
// @ref __imp__SetFocus@4=0079a38c
#include "shared/win_stub.hpp"
#include "shared/win32_api.hpp"
#include "shared/cd_timer.hpp"
#include "shared/debug_printf.hpp"
#include "shared/mouse.hpp"
#include "shared/dsurface.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_globals.hpp"

extern Surface *unknown_surface_839944;
HWND Unknown_00735B10();    // 0x00735B10 (the current dialog window)

void Focus_Restore()
{
    Debug_Printf("Focus_Restore()\n");
    Unknown_00406F70();
    Debug_Printf("Focus_Restore(): _MouseCaptured = %s\n", unknown_mouse_captured_b263e8 ? "true" : "false");
    if (WWMouse != 0 && unknown_mouse_captured_b263e8 == true && !unknown_a40d13) {
        WWMouse->Capture_Mouse();
    }
    if (!unknown_flag_851cb0) {
        if (unknown_surface_839958 != 0) {
            ((DSurface *)unknown_surface_839958)->Restore_Check();
        }
        if (unknown_surface_839954 != 0) {
            unknown_surface_839954->Restore_Check();
        }
        if (unknown_surface_839964 != 0) {
            if (((DSurface *)unknown_surface_839964)->Restore_Check() && (!unknown_flag_a40d04 || Frame > 0x10)) {
                unknown_surface_839964->Fill(0);
            }
        }
        if (unknown_surface_839944 != 0) {
            if (((DSurface *)unknown_surface_839944)->Restore_Check() && (!unknown_flag_a40d04 || Frame > 0x10)) {
                unknown_surface_839944->Fill(0);
            }
        }
        if (unknown_surface_839948 != 0) {
            if (((DSurface *)unknown_surface_839948)->Restore_Check()) {
                unknown_flag_8373c3 = true;
                if (!unknown_flag_a40d04 || Frame > 0x10) {
                    unknown_surface_839948->Fill(0);
                }
            }
        }
        if (unknown_surface_839950 != 0) {
            if (((DSurface *)unknown_surface_839950)->Restore_Check() && (!unknown_flag_a40d04 || Frame > 0x10)) {
                unknown_surface_839950->Fill_Rect(unknown_window_839640, 0);
            }
        }
    }
    Map.Flag_To_Redraw(2);
    InvalidateRect(MainWindow, 0, FALSE);
    Pause_Radar_Movie_005a0a90(false);
    if (Unknown_00735B10() != 0) {
        SetActiveWindow(Unknown_00735B10());
        SetFocus(Unknown_00735B10());
    }
}
