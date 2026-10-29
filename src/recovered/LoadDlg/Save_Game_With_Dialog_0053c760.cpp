// bool __stdcall Save_Game_With_Dialog(char const *filename, wchar_t const *description) (0x0053C760)
// Shows the "saving game" dialog (TXT_SAVING_GAME) while the game is written, then closes it.
#include "shared/load_dlg.hpp"
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_0BD@BKAO@D?3?2Ra2?2LoadDlg?4CPP?$AA@=007dfaa4
// @ref ?unknown_cancel_dialog_6001e0@@YIPAUHWND__@@PBG0PA_N@Z=006001e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ??_C@_0BA@HIPI@TXT_SAVING_GAME?$AA@=007d6a74
// @ref ?Unknown_006554A0@@YI_NPBDPBGH@Z=006554a0

bool __stdcall Save_Game_With_Dialog(char const *filename, wchar_t const *description)
{
    HWND dialog = unknown_cancel_dialog_6001e0(StringTable::Load_String("TXT_SAVING_GAME", 0, "D:\\Ra2\\LoadDlg.CPP", 0x453), 0, 0);
    WWMouse->Hide_Mouse();
    if (dialog) {
        unknown_dialog_5ff7c0(dialog);
    }
    bool saved = Unknown_006554A0(filename, description, 0);
    WWMouse->Show_Mouse();
    if (dialog) {
        unknown_dialog_5ff6e0(dialog);
    }
    return saved;
}
