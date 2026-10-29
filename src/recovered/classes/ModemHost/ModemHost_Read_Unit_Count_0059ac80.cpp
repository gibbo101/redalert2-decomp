// Read_Unit_Count_0059ac80 (0x0059AC80)
#include "shared/modem_host.hpp"
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_Unit_Count_0059ac80()
{
    HWND control = GetDlgItem(Window, 0x669);
    if (control) {
        unknown_session_a3d298.UnitCount = SendMessageA(control, 0x400, 0, 0);
        OptionsChanged = true;
    }
}
