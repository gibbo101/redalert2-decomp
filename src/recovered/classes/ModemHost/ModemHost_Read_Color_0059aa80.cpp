// Read_Color_0059aa80 (0x0059AA80)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_Color_0059aa80()
{
    HWND control = GetDlgItem(Window, 0x405);
    if (control) {
        int color = SendMessageA(control, 0x147, 0, 0);
        if (color != -1) {
            unknown_a3d3b4 = color;
            OptionsChanged = true;
            Changed = true;
            SendMessageA(control, 0x498, 0, Player_Color_RGB(color));
        }
    }
}
