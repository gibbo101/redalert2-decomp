// void __fastcall Open_Lobby_Dialog_005c6960(HWND parent) (0x005C6960)
#include "shared/lobby.hpp"
#include "shared/win32_window.hpp"
// @ref ?unknown_create_dialog_735700@@YIPAXPAXHPAUHWND__@@P6GJ1IIJ@ZJ@Z=00735700
// @ref ?unknown_show_dialog_5ff7e0@@YIXPAXH@Z=005ff7e0
// @ref ?Unknown_007359e0@@YIHPAUHWND__@@P6A_NXZHHH@Z=007359e0
// @ref ?Lobby_Dialog_Proc_005c69e0@@YGJPAUHWND__@@IIJ@Z=005c69e0
// @ref ?Lobby_Dialog_Update_005c67c0@@YA_NXZ=005c67c0
// @ref ?unknown_lobby_dialog_a728e0@@3PAUHWND__@@A=00a728e0

void __fastcall Open_Lobby_Dialog_005c6960(HWND parent)
{
    unknown_5159b0(0, true);
    unknown_lobby_dialog_a728e0 = (HWND)unknown_create_dialog_735700(ProgramInstance, 0x6B, parent, Lobby_Dialog_Proc_005c69e0, 0);
    unknown_show_dialog_5ff7e0(unknown_lobby_dialog_a728e0, 0x6B);
    SendMessageA(unknown_lobby_dialog_a728e0, 0x4A9, 0, 1);
    ShowWindow(unknown_lobby_dialog_a728e0, 1);
    Unknown_007359e0(unknown_lobby_dialog_a728e0, Lobby_Dialog_Update_005c67c0, 0, 1, 1);
}
