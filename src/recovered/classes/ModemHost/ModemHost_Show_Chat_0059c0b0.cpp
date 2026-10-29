// ModemHost::Show_Chat_0059c0b0 (0x0059C0B0)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/lobby.hpp"
#include "shared/comm_buffer.hpp"
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref ??_C@_1BA@FNA@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e1e78
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);

void ModemHost::Show_Chat_0059c0b0(unsigned short const *name, int color, unsigned short const *text)
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
