// ModemGuest::Dialog_Proc_00596170 (0x00596170)
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
// @ref ?Draw_0061D460@UnknownPreview_0061D430@@QAEXPAUHWND__@@@Z=0061d460
// @ref ?Read_Color_00597010@ModemGuest@@QAEXXZ=00597010
// @ref ?Read_Color_Entry_00596fc0@ModemGuest@@QAEXXZ=00596fc0
// @ref ?Read_Dialog_00596d50@ModemGuest@@QAEXXZ=00596d50
// @ref ?Read_Name_005970b0@ModemGuest@@QAEX_N@Z=005970b0
// @ref ?Send_Chat_00596e30@ModemGuest@@QAEXXZ=00596e30
// @ref ?Send_Ready_005974f0@ModemGuest@@QAEXXZ=005974f0
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410

extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);
extern unsigned short const unknown_empty_wide_839d4c[];

int __stdcall ModemGuest::Dialog_Proc_00596170(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result) {
        return result;
    }
    ModemGuest *guest = (ModemGuest *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x111:
        switch ((unsigned short)wparam) {
        case 1:
            if ((unsigned short)(wparam >> 16) == 0) {
                guest->Send_Ready_005974f0();
            }
            break;
        case 2:
            if ((unsigned short)(wparam >> 16) == 0) {
                guest->Read_Dialog_00596d50();
                guest->Result = 2;
            }
            break;
        case 0x405:
            if ((unsigned short)(wparam >> 16) == 1) {
                guest->Read_Color_00597010();
            }
            break;
        case 0x540:
            if ((unsigned short)(wparam >> 16) == 0x501) {
                guest->Send_Chat_00596e30();
            }
            break;
        case 0x5C1:
            if ((unsigned short)(wparam >> 16) == 0x501 || (unsigned short)(wparam >> 16) == 0x300) {
                guest->Read_Name_005970b0((unsigned short)(wparam >> 16) == 0x300);
            }
            break;
        case 0x667:
            if ((unsigned short)(wparam >> 16) == 1) {
                guest->Read_Color_Entry_00596fc0();
            }
            break;
        }
        break;
    case 0xF:
        if (unknown_dialog_preview_a72ce8) {
            unknown_dialog_preview_a72ce8->Draw_0061D460(window);
        }
        ValidateRect(window, 0);
        break;
    case 0x2:
        if (unknown_dialog_preview_a72ce8) {
            delete unknown_dialog_preview_a72ce8;
            unknown_dialog_preview_a72ce8 = 0;
        }
        break;
    }
    return 0;
}
