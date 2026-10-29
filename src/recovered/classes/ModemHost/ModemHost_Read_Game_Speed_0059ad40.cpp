// Read_Game_Speed_0059ad40 (0x0059AD40)
#include "shared/modem_host.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_Game_Speed_0059ad40()
{
    HWND control = GetDlgItem(Window, 0x529);
    if (control) {
        unknown_session_a3d298.GameSpeed_30 = 6 - SendMessageA(control, 0x400, 0, 0);
        OptionsChanged = true;
    }
}
