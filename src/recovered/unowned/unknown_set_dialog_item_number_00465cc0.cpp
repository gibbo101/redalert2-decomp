// void __fastcall unknown_set_dialog_item_number(HWND dialog, int id, int value) -- 0x00465CC0
// Purpose: formats a number as wide text (L"%d") and sends it to a dialog
// control with the custom message 0x4B2 (WM_USER + 0xB2). Referenced from
// the campaign score area; bound by linear sweep to the final ret.
#include "shared/win32_api.hpp"
#include "shared/string_table.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref _swprintf=00783764
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598

WIN32_IMPORT HWND __stdcall GetDlgItem(HWND dialog, int id);
WIN32_IMPORT long __stdcall SendMessageA(HWND window, unsigned int message, unsigned int wparam, long lparam);

void __fastcall unknown_set_dialog_item_number_00465cc0(HWND dialog, int id, int value)
{
    wchar_t text[32];
    swprintf(text, L"%d", value);
    HWND item = GetDlgItem(dialog, id);
    SendMessageA(item, 0x4b2, 0, (long)text);
}
