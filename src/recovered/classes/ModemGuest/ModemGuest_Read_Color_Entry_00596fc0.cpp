// ModemGuest::Read_Color_Entry_00596fc0 (0x00596FC0)
#include "shared/modem_guest.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/null_dlg.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_preview.hpp"
#include "shared/options_dialog.hpp"
// @ref ?unknown_a3d3bc@@3HA=00a3d3bc
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
void ModemGuest::Read_Color_Entry_00596fc0()
{
    HWND control = GetDlgItem(Window, 0x667);
    if (control) {
        int row = SendMessageA(control, 0x147, 0, 0);
        if (row != -1) {
            unknown_a3d3bc = SendMessageA(control, 0x150, row, 0);
            OptionsChanged = true;
            Changed = true;
        }
    }
}
