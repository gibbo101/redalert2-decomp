// @ref ?DialogStack@@3PAUDialogStackEntry@@A=00b25bb8
// @ref ?CurrentDialog@@3PAUHWND__@@A=00b25dd4
// @ref ?CurrentDialogResource@@3HA=00b25dd8
// @ref ?DialogStackCount@@3HA=00b25de0
// @ref ?ProgramInstance@@3PAXA=00b26180
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Load_Resource_004954e0@@YIPAXIPBD@Z=004954e0
// @ref ?Unknown_005B6000@@YIXPAUHWND__@@@Z=005b6000
// @ref __imp__CreateDialogIndirectParamA@20=0079a448
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/queue.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"

// Creates a modeless dialog from template resource with the main window as its parent and pushes it
// on the dialog stack as the current dialog; 0 when the template is missing or creation fails (0x005FF610).
HWND __fastcall unknown_create_dialog_5ff610(int resource, DialogProc proc, int unknown3)
{
    unsigned short id = (unsigned short)resource;
    DLGTEMPLATE const *dialog_template = (DLGTEMPLATE const *)Load_Resource_004954e0(id, (char const *)5);
    if (!dialog_template) {
        return 0;
    }
    int index = DialogStackCount;
    UnknownDialogCreateParam param;
    DialogStack[index].Window = 0;
    DialogStack[index].Resource = 0;
    DialogStackCount++;
    param.Resource = id;
    param.Param = unknown3;
    HWND window = CreateDialogIndirectParamA(ProgramInstance, dialog_template, MainWindow, (DLGPROC)proc, (LPARAM)&param);
    if (!window) {
        DialogStackCount--;
        return 0;
    }
    DialogStack[index].Window = window;
    DialogStack[index].Resource = id;
    Unknown_005B6000(window);
    CurrentDialog = window;
    CurrentDialogResource = id;
    return window;
}
