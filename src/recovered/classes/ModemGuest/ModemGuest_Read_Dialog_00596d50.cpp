// ModemGuest::Read_Dialog_00596d50 (0x00596D50)
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
// @ref ??_C@_0BN@COBG@ModemGuest?4ReadDialog?$CIexit?$CJ?6?$AA@=007e2054
// @ref ??_C@_0BO@CBCF@ModemGuest?4ReadDialog?$CIenter?$CJ?6?$AA@=007e2080
// @ref ??_C@_0L@HPID@Color?3?5?$CFd?6?$AA@=007e1fa8
// @ref ?Unknown_006FA0F0@@YIXPADPBGH@Z=006fa0f0
// @ref ??_C@_09FJEP@Name?3?5?$CFs?6?$AA@=007e2074
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_a3d3bc@@3HA=00a3d3bc
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ??_C@_09FJEP@Name?3?5?$CFs?6?$AA@=007e2074
void ModemGuest::Read_Dialog_00596d50()
{
    unsigned short name[20];
    Debug_Printf("ModemGuest.ReadDialog(enter)\n");
    HWND control = GetDlgItem(Window, 0x5C1);
    if (control) {
        SendMessageA(control, 0x4B3, 20, (LPARAM)name);
        Unknown_006FA0F0(unknown_name_a3d3a0, name, -1);
    }
    Debug_Printf("Name: %s\n", unknown_name_a3d3a0);
    control = GetDlgItem(Window, 0x405);
    if (control) {
        unknown_a3d3b4 = SendMessageA(control, 0x147, 0, 0);
    }
    Debug_Printf("Color: %d\n", unknown_a3d3b4);
    control = GetDlgItem(Window, 0x667);
    if (control) {
        int selection = SendMessageA(control, 0x147, 0, 0);
        unknown_a3d3bc = SendMessageA(control, 0x150, selection, 0);
    }
    Debug_Printf("ModemGuest.ReadDialog(exit)\n");
}
