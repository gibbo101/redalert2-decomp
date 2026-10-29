// ModemGuest::Send_Chat_00596e30 (0x00596E30)
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
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?Send_Chat_00598400@ModemGuest@@QAEXPBG@Z=00598400
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);
extern unsigned short const unknown_empty_wide_839d4c[];

void ModemGuest::Send_Chat_00596e30()
{
    unsigned short text[256];
    HWND control = GetDlgItem(Window, 0x540);
    if (control) {
        SendMessageA(control, 0x4B3, 256, (LPARAM)text);
        SendMessageA(control, 0x4B2, 0, (LPARAM)unknown_empty_wide_839d4c);
        if (wcslen(text) && text[0] != 0x0D) {
            wcstrim(text);
            Send_Chat_00598400(text);
        }
    }
}
