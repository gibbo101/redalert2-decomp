// void *__fastcall unknown_create_dialog_735700(void *instance, int id, HWND parent,
//     UnknownDialogProc procedure, long arg) (0x00735700)
// @ref ?Load_Resource_004954e0@@YIPAXIPBD@Z=004954e0
// @ref ?unknown_int_a40d34@@3HA=00a40d34
// @ref ?Unknown_005B6000@@YIXPAUHWND__@@@Z=005b6000
// @ref ?unknown_prepare_control_735bc0@@YGHPAUHWND__@@J@Z=00735bc0
// @ref ?DialogStack@@3PAUDialogStackEntry@@A=00b25bb8
// @ref ?DialogStackCount@@3HA=00b25de0
// @ref ?CurrentDialog@@3PAUHWND__@@A=00b25dd4
// @ref ?CurrentDialogResource@@3HA=00b25dd8
#include "shared/win_util.hpp"
#include "shared/win32_window.hpp"

void *__fastcall unknown_create_dialog_735700(void *instance, int id, HWND parent, UnknownDialogProc procedure, long arg)
{
    DialogStack[DialogStackCount].Window = 0;
    DialogStack[DialogStackCount].Resource = 0;
    DialogStackEntry *entry = &DialogStack[DialogStackCount];
    DLGTEMPLATE const *dialog_template = (DLGTEMPLATE const *)Load_Resource_004954e0(id, (char const *)5);   // RT_DIALOG
    if (dialog_template == 0) {
        return 0;
    }
    DialogStackCount++;
    HWND dialog = CreateDialogIndirectParamA((HINSTANCE)instance, dialog_template, parent, (DLGPROC)procedure, 0);
    if (dialog == 0) {
        DialogStackCount--;
        return 0;
    }
    unknown_int_a40d34++;
    Unknown_005B6000(dialog);
    EnumChildWindows(dialog, unknown_prepare_control_735bc0, 1);
    unknown_prepare_control_735bc0(dialog, 0);
    entry->Window = dialog;
    entry->Resource = id;
    if (arg != 0) {
        ShowWindow(dialog, 1);   // SW_SHOWNORMAL
    }
    SetForegroundWindow(dialog);
    SetFocus(dialog);
    CurrentDialog = dialog;
    CurrentDialogResource = id;
    return dialog;
}
