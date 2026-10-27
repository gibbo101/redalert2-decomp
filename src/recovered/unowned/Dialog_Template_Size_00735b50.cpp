// int __fastcall Dialog_Template_Size(int dialog_id, DLGPROC procedure, int unused, LONG *size) -- 0x00735B50
// Purpose: measures a dialog template: creates it (ProgramInstance, no
// parent, init parameter 0), stores its client width and height in size[0]
// and size[1], destroys it and returns 1. The third argument is not read.
#include "shared/win32_window.hpp"
// @ref ?ProgramInstance@@3PAXA=00b26180

int __fastcall Dialog_Template_Size(int dialog_id, DLGPROC procedure, int unused, LONG *size)
{
    HWND dialog;
    RECT client;

    dialog = CreateDialogParamA(ProgramInstance, MAKEINTRESOURCEA(dialog_id), 0, procedure, 0);
    GetClientRect(dialog, &client);
    DestroyWindow(dialog);
    size[0] = client.right;
    size[1] = client.bottom;
    return 1;
}
