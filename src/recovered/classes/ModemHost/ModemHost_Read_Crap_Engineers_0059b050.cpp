// Read_Crap_Engineers_0059b050 (0x0059B050)
#include "shared/modem_host.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_Crap_Engineers_0059b050()
{
    HWND control = GetDlgItem(Window, 0x551);
    if (control) {
        unknown_session_a3d298.unknown_34 = SendMessageA(control, 0xF0, 0, 0) == 1;
        OptionsChanged = true;
    }
}
