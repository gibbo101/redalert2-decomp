// ModemGuest::Show_Chat_00598510 (0x00598510)
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
// @ref ??_C@_1BA@FNA@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e1e78
// @ref ?Unknown_005C2DA0@@YIXHPBGPAUHWND__@@@Z=005c2da0
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);

void ModemGuest::Show_Chat_00598510(unsigned short const *name, int color, unsigned short const *text)
{
    if (text) {
        HWND list = GetDlgItem(Window, 0x53F);
        if (list) {
            int rgb = Player_Color_RGB(color);
            unsigned short line[256];
            swprintf(line, L"[%s] %s", name, text);
            Unknown_005C2DA0(rgb, line, list);
        }
    }
}
