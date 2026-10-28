// LRESULT __fastcall Unknown_Set_Time_Text_0069A6F0(HWND dialog, int id, int seconds) (0x0069A6F0)
// Formats a number of seconds as "hh:mm:ss" and sends it to the dialog item as text (message 0x4B2).
// The hours/minutes/seconds split is by subtracting the quotients (a % would use idiv).
// @ref _swprintf=00783764
// @ref ??_C@_1BO@ECFI@?$AA?$CF?$AA0?$AA2?$AAd?$AA?3?$AA?$CF?$AA0?$AA2?$AAd?$AA?3?$AA?$CF?$AA0?$AA2?$AAd?$AA?$AA@=007f62a8
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
#include "shared/win32_api.hpp"
#include "shared/string_table.hpp"

LRESULT __fastcall Unknown_Set_Time_Text_0069A6F0(HWND dialog, int id, int seconds)
{
    wchar_t text[32];
    int minutes = seconds / 60;
    int hours = minutes / 60;
    int seconds_left = seconds - minutes * 60;
    int minutes_left = minutes - hours * 60;
    swprintf(text, L"%02d:%02d:%02d", hours, minutes_left, seconds_left);
    HWND item = GetDlgItem(dialog, id);
    return SendMessageA(item, 0x4B2, 0, (LPARAM)text);
}
