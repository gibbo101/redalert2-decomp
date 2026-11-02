// Handles the save dialog's controls: picking a listed game copies its description into the edit field (0x0053B280).
#include "shared/load_dlg.hpp"

void __fastcall LoadOptionsClass::Save_Dialog_On_WM_COMMAND(HWND window, int id, HWND control, int code)
{
    LoadOptionsClass *options = (LoadOptionsClass *)GetWindowLongA(window, 8);
    switch (id) {
    case 0x527:
        if (code == 1 && SendMessageA(control, 0x18b, 0, 0) > 0) {
            int row = SendMessageA(control, 0x188, 0, 0);
            if (row != -1) {
                FileEntryClass *entry = (FileEntryClass *)SendMessageA(control, 0x199, row, 0);
                if (entry->HasDescription && !entry->NeedsDescription) {
                    HWND edit = GetDlgItem(window, 0x526);
                    SendMessageA(edit, 0x4b2, 0, (LPARAM)entry->Description);
                } else {
                    wchar_t *text = options->Description;
                    if (text != 0) {
                        HWND edit = GetDlgItem(window, 0x526);
                        SendMessageA(edit, 0x4b2, 0, (LPARAM)text);
                    }
                }
                SetFocus(GetDlgItem(window, 0x526));
                SendMessageA(GetDlgItem(window, 0x526), 0xb1, 0, -1);
            }
        }
        break;
    case 0x686:
        if (code == 0) {
            options->State = 2;
        }
        break;
    case 0x6c7:
        if (code == 0) {
            options->State = 1;
        }
        break;
    }
}
