// BOOL __stdcall Unknown_00627350(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam) (0x00627350):
// the reconnect dialog's window procedure.
#include "shared/queue.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/wol_sink.hpp"
#include "shared/mouse.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_ab62ec@@3HA=00ab62ec
// @ref ?unknown_ab62f0@@3HA=00ab62f0
// @ref ?unknown_ab62f4@@3_NA=00ab62f4
// @ref ?unknown_ab62f5@@3_NA=00ab62f5
// @ref ?unknown_ab62e0@@3_NA=00ab62e0
// @ref ?unknown_ab62f8@@3HA=00ab62f8
// @ref ?unknown_kick_buttons_7ec3f8@@3PAHA=007ec3f8
// @ref ?unknown_timing_bars_7ec418@@3PAHA=007ec418
// @ref ?Unknown_00626CB0@@YIXPAUHWND__@@@Z=00626cb0
// @ref ?Unknown_005B6000@@YIXPAUHWND__@@@Z=005b6000
// @ref ?Unknown_005B6060@@YIXPAUHWND__@@@Z=005b6060
// @ref ?Unknown_005FEE70@@YIXPAUHWND__@@@Z=005fee70
// @ref ?Unknown_005FE380@@YIXJ@Z=005fe380
// @ref ?Propose_Kick_Player@@YIXPAUHWND__@@H@Z=00626fe0

BOOL __stdcall Unknown_00627350(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam)
{
    int *result = (int *)GetWindowLongA(dialog, 8);     // DWL_USER
    HWND button;
    HWND bar;
    int i;

    switch (message) {
    case 0x0002:        // WM_DESTROY
        Unknown_005B6060(dialog);
        return FALSE;
    case 0x002B:        // WM_DRAWITEM
        Unknown_005FE380(lparam);
        return TRUE;
    case 0x0014:        // WM_ERASEBKGND
        return TRUE;
    case 0x000F:        // WM_PAINT
        Unknown_005FEE70(dialog);
        Unknown_00626CB0(dialog);
        ValidateRect(dialog, 0);
        return FALSE;
    case 0x0111:        // WM_COMMAND
        switch ((unsigned short)wparam) {
        case 2:         // IDCANCEL
            *result = 2;
            return FALSE;
        case 0x640:
            Propose_Kick_Player(dialog, 0);
            return FALSE;
        case 0x642:
            Propose_Kick_Player(dialog, 1);
            return FALSE;
        case 0x641:
            Propose_Kick_Player(dialog, 2);
            return FALSE;
        case 0x643:
            Propose_Kick_Player(dialog, 3);
            return FALSE;
        case 0x644:
            Propose_Kick_Player(dialog, 4);
            return FALSE;
        case 0x645:
            Propose_Kick_Player(dialog, 5);
            return FALSE;
        case 0x646:
            Propose_Kick_Player(dialog, 6);
            return FALSE;
        case 0x647:
            Propose_Kick_Player(dialog, 7);
            return FALSE;
        }
        break;
    case 0x0113:        // WM_TIMER
        if (unknown_session_a3d298.Type == 4 && wparam == 1 && unknown_ladder_client_a72d00) {
            if (unknown_b2a630 < 5) {
                int handle;
                unknown_ladder_client_a72d00->Request_Ping(unknown_game_address_b2a758, 1000, &handle);
                unknown_b2a630++;
            }
            unknown_ab62f8++;
            if (unknown_b2a7ec) {
                if (!unknown_ab62f4 && unknown_ab62f8 > 5 && !unknown_b2aaf8) {
                    unknown_ab62f4 = true;
                    unknown_ab62ec++;
                } else if (!unknown_ab62f5 && unknown_ab62f8 > 10 && !unknown_b2aaf8) {
                    unknown_ab62f5 = true;
                    unknown_ab62f0++;
                }
                if (unknown_ab62ec > 5 || unknown_ab62f0 > 2) {
                    unknown_ab62e0 = true;
                    *result = 2;
                    return FALSE;
                }
            }
            SetTimer(dialog, 1, 1000, 0);
        }
        break;
    case 0x0132:        // WM_CTLCOLORMSGBOX .. WM_CTLCOLORSTATIC
    case 0x0133:
    case 0x0134:
    case 0x0135:
    case 0x0136:
    case 0x0137:
    case 0x0138:
        return (BOOL)GetStockObject(4);      // BLACK_BRUSH
    case 0x0497: {      // WM_USER + 0x97: set up
        Unknown_005B6000(dialog);
        for (i = 0; i < 8; i++) {
            button = GetDlgItem(dialog, unknown_kick_buttons_7ec3f8[i]);
            EnableWindow(button, FALSE);
            bar = GetDlgItem(dialog, unknown_timing_bars_7ec418[i]);
            EnableWindow(bar, FALSE);
        }
        for (i = 0; i < 8; i++) {
            button = GetDlgItem(dialog, unknown_kick_buttons_7ec3f8[i]);
            bar = GetDlgItem(dialog, unknown_timing_bars_7ec418[i]);
            if (i < unknown_session_a3d298.Players.Count()) {
                SendMessageA(button, 0x04B2, 0, (LPARAM)unknown_session_a3d298.Players[i]);
                EnableWindow(button, TRUE);
                EnableWindow(bar, TRUE);
            } else {
                DestroyWindow(button);
                DestroyWindow(bar);
            }
        }
        if (unknown_session_a3d298.Type == 4) {
            unknown_b2a630 = 0;
            unknown_b2aaf8 = 0;
            unknown_ab62f4 = false;
            unknown_ab62f5 = false;
            unknown_ab62f8 = 0;
            unknown_ab62e0 = false;
            SetTimer(dialog, 1, 1000, 0);
        }
        WWMouse->Show_Mouse();
        break;
    }
    }
    return FALSE;
}
