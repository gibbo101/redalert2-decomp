// Set_Guest_0059ab80 (0x0059AB80)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??_C@_1BA@DLOG@?$AA?$CF?$AAs?$AA?5?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?$AA@=007e20a0
extern "C" int __cdecl _wcsicmp(unsigned short const *left, unsigned short const *right);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);

void ModemHost::Set_Guest_0059ab80(unsigned short const *name, int color, int house)
{
    if (_wcsicmp(GuestName, name) || GuestColor != color || GuestHouse != house) {
        wcscpy(GuestName, name);
        GuestColor = color;
        GuestHouse = house;
        HWND control = GetDlgItem(Window, 0x668);
        if (control) {
            unsigned short text[80];
            swprintf(text, L"%s [%s]", name, HouseTypes[house]->UIName);
            SendMessageA(control, 0x4B2, 0, (LPARAM)text);
            SendMessageA(control, 0x498, 0, Player_Color_RGB(color));
        }
        Voc_Play(Rules->OptionsChanged, 1.0f, 0x2000, 0);
    }
    OptionsChanged = true;
}
