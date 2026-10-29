// ModemGuest::Read_Color_00597010 (0x00597010)
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
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
void ModemGuest::Read_Color_00597010()
{
    HWND control = GetDlgItem(Window, 0x405);
    if (control) {
        int color = SendMessageA(control, 0x147, 0, 0);
        if (color != -1) {
            if (color == HostColor) {
                color = HostColor + 1;
                if (color > 7) {
                    color = 0;
                }
                SendMessageA(control, 0x14E, color, 0);
            }
            unknown_a3d3b4 = color;
            OptionsChanged = true;
            Changed = true;
            int rgb;
            if (color >= 0 && color < 8) {
                rgb = unknown_color_values_7e6d94[color];
            } else {
                rgb = unknown_color_7a737c;
            }
            SendMessageA(control, 0x498, 0, rgb);
        }
    }
}
