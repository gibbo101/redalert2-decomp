// void UnknownModemGuest::ReadDialog_00596d50() (0x00596D50)
// Reads the modem guest's setup dialog: the name (control 0x5C1, message 0x4B3 into a wide buffer,
// narrowed into the local nick name), the colour list's selection (control 0x405 into 0xA3D3B4)
// and the colour entry's item data (control 0x667 into 0xA3D3BC).
#include "shared/modem_guest.hpp"
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_a3d3bc@@3HA=00a3d3bc
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?Unknown_006FA0F0@@YIXPADPBGH@Z=006fa0f0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BO@CBCF@ModemGuest?4ReadDialog?$CIenter?$CJ?6?$AA@=007e2080
// @ref ??_C@_09FJEP@Name?3?5?$CFs?6?$AA@=007e2074
// @ref ??_C@_0L@HPID@Color?3?5?$CFd?6?$AA@=007e1fa8
// @ref ??_C@_0BN@COBG@ModemGuest?4ReadDialog?$CIexit?$CJ?6?$AA@=007e2054
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0

void UnknownModemGuest::ReadDialog_00596d50()
{
    UnknownModemGuest *dialog = this;
    unsigned short name[20];
    Debug_Printf("ModemGuest.ReadDialog(enter)\n");
    HWND control = GetDlgItem(dialog->Window, 0x5C1);
    if (control) {
        SendMessageA(control, 0x4B3, 20, (LPARAM)name);
        Unknown_006FA0F0(unknown_name_a3d3a0, name, -1);
    }
    Debug_Printf("Name: %s\n", unknown_name_a3d3a0);
    control = GetDlgItem(dialog->Window, 0x405);
    if (control) {
        unknown_a3d3b4 = SendMessageA(control, 0x147, 0, 0);
    }
    Debug_Printf("Color: %d\n", unknown_a3d3b4);
    control = GetDlgItem(dialog->Window, 0x667);
    if (control) {
        int selection = SendMessageA(control, 0x147, 0, 0);
        unknown_a3d3bc = SendMessageA(control, 0x150, selection, 0);
    }
    Debug_Printf("ModemGuest.ReadDialog(exit)\n");
}
