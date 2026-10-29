// ModemGuest::Set_Host_00597130 (0x00597130)
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
// @ref ??_C@_1BA@DLOG@?$AA?$CF?$AAs?$AA?5?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?$AA@=007e20a0
// @ref ?Read_Color_00597010@ModemGuest@@QAEXXZ=00597010
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);

void ModemGuest::Set_Host_00597130(unsigned short const *name, int color, int house)
{
    wcscpy(HostName, name);
    HostColor = color;
    HWND control = GetDlgItem(Window, 0x405);
    if (control) {
        int selection = SendMessageA(control, 0x147, 0, 0);
        if (selection != -1 && selection == HostColor) {
            Read_Color_00597010();
        }
    }
    HostHouse = house;
    control = GetDlgItem(Window, 0x668);
    if (control) {
        unsigned short text[80];
        swprintf(text, L"%s [%s]", name, HouseTypes[house]->UIName);
        SendMessageA(control, 0x4B2, 0, (LPARAM)text);
        SendMessageA(control, 0x498, 0, Player_Color_RGB(color));
    }
}
