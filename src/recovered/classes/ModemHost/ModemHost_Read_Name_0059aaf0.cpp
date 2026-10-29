// Read_Name_0059aaf0 (0x0059AAF0)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void ModemHost::Read_Name_0059aaf0(bool keep)
{
    HWND control = GetDlgItem(Window, 0x5C1);
    if (control) {
        unsigned short name[20];
        SendMessageA(control, 0x4B3, 20, (LPARAM)name);
        wcstrim(name);
        if (!keep) {
            SendMessageA(control, 0x4B2, 0, (LPARAM)name);
        }
        strcpy(unknown_name_a3d3a0, Unknown_006FA120(name));
        OptionsChanged = true;
        Changed = true;
    }
}
