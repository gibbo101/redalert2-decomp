// ModemGuest::Read_Name_005970b0 (0x005970B0)
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
// @ref ?Unknown_006FA0F0@@YIXPADPBGH@Z=006fa0f0
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
void ModemGuest::Read_Name_005970b0(bool keep)
{
    HWND control = GetDlgItem(Window, 0x5C1);
    if (control) {
        unsigned short name[21];
        SendMessageA(control, 0x4B3, 21, (LPARAM)name);
        wcstrim(name);
        if (!keep) {
            SendMessageA(control, 0x4B2, 0, (LPARAM)name);
        }
        Unknown_006FA0F0(unknown_name_a3d3a0, name, -1);
        OptionsChanged = true;
        Changed = true;
    }
}
