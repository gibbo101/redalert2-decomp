#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/win32_api.hpp"
void __fastcall Open_Page_Dialog_007560e0()
{
    HWND dialog=(HWND)unknown_create_dialog_735700(ProgramInstance,0x11e,MainWindow,(UnknownDialogProc)Page_Dialog_Proc_00757d80,0);
    unknown_show_dialog_5ff7e0(dialog,0x11e);
    SendMessageA(dialog,0x4a9,0,1);
    ShowWindow(dialog,1);
    Unknown_007359e0(dialog,Unknown_0073e100,0,1,1);
}
