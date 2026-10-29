// Read_AI_Difficulty_0059ad80 (0x0059AD80)
#include "shared/modem_host.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_AI_Difficulty_0059ad80()
{
    HWND control = GetDlgItem(Window, 0x553);
    if (control) {
        unknown_session_a3d298.unknown_difficulty_40 = SendMessageA(control, 0x400, 0, 0);
        OptionsChanged = true;
    }
}
