// Read_Crates_0059ae60 (0x0059AE60)
#include "shared/modem_host.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_Crates_0059ae60()
{
    HWND control = GetDlgItem(Window, 0x54C);
    if (control) {
        unknown_session_a3d298.unknown_crates_29 = SendMessageA(control, 0xF0, 0, 0) == 1;
        OptionsChanged = true;
    }
}
