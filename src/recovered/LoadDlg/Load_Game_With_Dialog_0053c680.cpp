// bool __stdcall Load_Game_With_Dialog(char const *filename) (0x0053C680)
// Shows the "loading" dialog (text TXT_LOADING) with the mouse hidden, loads the game, then restores
// the mouse hide count and closes the dialog.
#include "shared/load_dlg.hpp"
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_0BD@BKAO@D?3?2Ra2?2LoadDlg?4CPP?$AA@=007dfaa4
// @ref ?unknown_cancel_dialog_6001e0@@YIPAUHWND__@@PBG0PA_N@Z=006001e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ??_C@_0M@KNKK@TXT_LOADING?$AA@=007dfad4
// @ref ?unknown_flag_a40d04@@3_NA=00a40d04
// @ref ?unknown_flag_a40380@@3_NA=00a40380
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?Unknown_00672E70@UnknownSessionState@@QAEXXZ=00672e70
// @ref ?Unknown_00656890@@YI_NPBD@Z=00656890

bool __stdcall Load_Game_With_Dialog(char const *filename)
{
    int mouse_state = WWMouse->Get_Mouse_State();
    HWND dialog = unknown_cancel_dialog_6001e0(StringTable::Load_String("TXT_LOADING", 0, "D:\\Ra2\\LoadDlg.CPP", 0x41C), 0, 0);
    WWMouse->Hide_Mouse();
    if (dialog) {
        unknown_dialog_5ff7c0(dialog);
    }
    unknown_flag_a40d04 = false;
    unknown_flag_a40380 = false;
    unknown_session_a3d298.Unknown_00672E70();
    bool loaded = Unknown_00656890(filename);
    while (WWMouse->Get_Mouse_State() < mouse_state) {
        WWMouse->Show_Mouse();
    }
    while (WWMouse->Get_Mouse_State() > mouse_state) {
        WWMouse->Hide_Mouse();
    }
    if (dialog) {
        unknown_dialog_5ff6e0(dialog);
    }
    return loaded;
}
