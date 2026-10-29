// Read_AI_Players_0059ad10 (0x0059AD10)
#include "shared/modem_host.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_AI_Players_0059ad10()
{
    HWND control = GetDlgItem(Window, 0x552);
    if (control) {
        unknown_session_a3d298.AICount = SendMessageA(control, 0x400, 0, 0);
        OptionsChanged = true;
    }
}
