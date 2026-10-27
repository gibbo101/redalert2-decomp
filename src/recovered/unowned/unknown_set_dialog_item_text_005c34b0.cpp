// void __fastcall unknown_set_dialog_item_text(HWND dialog) -- 0x005C34B0
// Purpose: sends the custom message 0x4B2 (WM_USER + 0xB2) with the text
// at 0x00A3D342 to dialog control 0x5A8. No direct callers.
#include "shared/win32_api.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?unknown_text_a3d342@@3PADA=00a3d342

WIN32_IMPORT HWND __stdcall GetDlgItem(HWND dialog, int id);
WIN32_IMPORT long __stdcall SendMessageA(HWND window, unsigned int message, unsigned int wparam, long lparam);

extern char unknown_text_a3d342[];

void __fastcall unknown_set_dialog_item_text_005c34b0(HWND dialog)
{
    HWND item = GetDlgItem(dialog, 0x5a8);
    SendMessageA(item, 0x4b2, 0, (long)unknown_text_a3d342);
}
