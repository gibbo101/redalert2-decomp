// Read_Tech_Level_0059acb0 (0x0059ACB0)
#include "shared/modem_host.hpp"
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_Tech_Level_0059acb0()
{
    HWND control = GetDlgItem(Window, 0x550);
    if (control) {
        unknown_house_setting_7d88d8 = SendMessageA(control, 0x400, 0, 0);
        OptionsChanged = true;
    }
}
