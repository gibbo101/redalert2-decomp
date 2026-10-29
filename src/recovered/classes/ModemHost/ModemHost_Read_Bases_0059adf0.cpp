// Read_Bases_0059adf0 (0x0059ADF0)
#include "shared/modem_host.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__SendDlgItemMessageA@20=0079a484

void ModemHost::Read_Bases_0059adf0()
{
    HWND control = GetDlgItem(Window, 0x66A);
    if (control) {
        unknown_session_a3d298.unknown_bases_20 = SendMessageA(control, 0xF0, 0, 0) == 1;
        if (!unknown_session_a3d298.unknown_bases_20) {
            if (GetDlgItem(Window, 0x54E)) {
                unknown_session_a3d298.unknown_2a = false;
                SendDlgItemMessageA(Window, 0x54E, 0xF1, 0, 0);
            }
        }
        OptionsChanged = true;
    }
}
