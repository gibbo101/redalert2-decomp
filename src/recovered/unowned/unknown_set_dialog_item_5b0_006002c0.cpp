// void __fastcall unknown_set_dialog_item_5b0(HWND dialog, LPARAM value) -- 0x006002C0
// Purpose: sends message 0x4B2 with value to control 0x5B0 of dialog and
// repaints the dialog (UpdateWindow).
// Assumptions: what control 0x5B0 and message 0x4B2 are is unknown.
#include "shared/win32_api.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__UpdateWindow@4=0079a46c

WIN32_IMPORT BOOL WINAPI UpdateWindow(HWND window);

void __fastcall unknown_set_dialog_item_5b0(HWND dialog, LPARAM value)
{
    HWND item = GetDlgItem(dialog, 0x5B0);
    SendMessageA(item, 0x4B2, 0, value);
    UpdateWindow(dialog);
}
