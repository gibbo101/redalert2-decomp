// Send_Chat_0059a880 (0x0059A880)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??_C@_1BA@FNA@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e1e78
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);
extern unsigned short const unknown_empty_wide_839d4c[];

void ModemHost::Send_Chat_0059a880()
{
    unsigned short text[256];
    memset(text, 0, sizeof(text));
    HWND control = GetDlgItem(Window, 0x540);
    if (control) {
        SendMessageA(control, 0x4B3, 256, (LPARAM)text);
        SendMessageA(control, 0x4B2, 0, (LPARAM)unknown_empty_wide_839d4c);
        if (wcslen(text) && text[0] != 0x0D) {
            wcstrim(text);
            if (text) {
                UnknownSerialPacket packet;
                memset(&packet, 0, sizeof(packet));
                packet.Command = 0x68;
                strcpy(packet.Name, unknown_name_a3d3a0);
                packet.ID = unknown_a3d3b4;
                wcscpy(packet.Message, text);
                serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
                serial_manager_00a40a28.Service();
                unsigned short *name = Unknown_006FA180(unknown_name_a3d3a0);
                int color = unknown_a3d3b4;
                HWND list = GetDlgItem(Window, 0x53F);
                if (list) {
                    int rgb = Player_Color_RGB(color);
                    unsigned short line[256];
                    swprintf(line, L"[%s] %s", name, text);
                    Unknown_005C2DA0(rgb, line, list);
                }
            }
        }
    }
}
