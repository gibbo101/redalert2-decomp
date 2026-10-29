// Read_unknown_2b_0059afd0 (0x0059AFD0)
#include "shared/modem_host.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_unknown_2b_0059afd0()
{
    HWND control = GetDlgItem(Window, 0x69A);
    if (control) {
        unknown_session_a3d298.unknown_2b = SendMessageA(control, 0xF0, 0, 0) == 1;
        OptionsChanged = true;
    }
}
