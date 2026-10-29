// Read_Credits_0059ace0 (0x0059ACE0)
#include "shared/modem_host.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_Credits_0059ace0()
{
    HWND control = GetDlgItem(Window, 0x402);
    if (control) {
        unknown_session_a3d298.unknown_24 = SendMessageA(control, 0x400, 0, 0);
        OptionsChanged = true;
    }
}
