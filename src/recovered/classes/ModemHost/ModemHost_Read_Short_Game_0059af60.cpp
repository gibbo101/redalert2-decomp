// Read_Short_Game_0059af60 (0x0059AF60)
#include "shared/modem_host.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__SendDlgItemMessageA@20=0079a484

void ModemHost::Read_Short_Game_0059af60()
{
    HWND control = GetDlgItem(Window, 0x54E);
    if (control) {
        int state = SendMessageA(control, 0xF0, 0, 0);
        bool checked = state == 1;
        unknown_session_a3d298.unknown_2a = checked;
        OptionsChanged = true;
        if (unknown_session_a3d298.unknown_2a) {
            if (GetDlgItem(Window, 0x66A)) {
                unknown_session_a3d298.unknown_bases_20 = true;
                SendDlgItemMessageA(Window, 0x66A, 0xF1, 1, 0);
            }
        }
    }
}
