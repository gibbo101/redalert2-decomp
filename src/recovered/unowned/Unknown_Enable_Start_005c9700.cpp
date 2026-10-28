// void Unknown_Enable_Start_005c9700() (0x005C9700)
// Unless the current dialog is 0xBC, enables control 0x59F of the first dialog found among
// the ids 0xC2, 0xC9, 0xBC and 0xBD; then clears unknown_67 of every session entry whose
// name is not the host's.
#include "shared/lobby.hpp"
#include "shared/win32_api.hpp"
// @ref __imp__EnableWindow@8=0079a490
// @ref __imp__GetDlgItem@8=0079a49c
// @ref ?Current_Dialog_Id_00735b20@@YAHXZ=00735b20
// @ref ?Find_Dialog_00735940@@YIPAUHWND__@@H@Z=00735940
// @ref ?Compare_Wide_007837d3@@YAHPBG0@Z=007837d3
// @ref ?unknown_host_name_a3f618@@3PAGA=00a3f618
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c

void Unknown_Enable_Start_005c9700()
{
    if (Current_Dialog_Id_00735b20() != 0xbc) {
        HWND dialog = Find_Dialog_00735940(0xc2);
        if (dialog == 0) {
            dialog = Find_Dialog_00735940(0xc9);
            if (dialog == 0) {
                dialog = Find_Dialog_00735940(0xbc);
                if (dialog == 0) {
                    dialog = Find_Dialog_00735940(0xbd);
                }
            }
        }
        EnableWindow(GetDlgItem(dialog, 0x59f), 1);
    }
    int count = unknown_players_a3fa7c.Count();
    for (int i = 0; i < count; i++) {
        if (Compare_Wide_007837d3(unknown_players_a3fa7c[i]->Name, unknown_host_name_a3f618) != 0 &&
            unknown_players_a3fa7c[i]->unknown_67 != 0) {
            unknown_players_a3fa7c[i]->unknown_67 = 0;
        }
    }
}
