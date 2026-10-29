// Read_Color_Entry_0059aa20 (0x0059AA20)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
// @ref ?unknown_a3d3bc@@3HA=00a3d3bc
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_Color_Entry_0059aa20()
{
    HWND control = GetDlgItem(Window, 0x667);
    if (control) {
        int row = SendMessageA(control, 0x147, 0, 0);
        if (row != -1) {
            int entry = SendMessageA(control, 0x150, row, 0);
            if (entry != -1) {
                unknown_a3d3bc = entry;
                OptionsChanged = true;
                Changed = true;
            }
        }
    }
}
