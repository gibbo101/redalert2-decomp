// void __fastcall unknown_set_dialog_item_number(HWND dialog, int id, int value) -- 0x00467240
// The campaign end screen's copy of 0x00465CC0: sends value as decimal text (L"%d") to the
// dialog control id with the custom message 0x4B2.
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref _swprintf=00783764
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
#include "shared/win32_api.hpp"
#include "shared/string_table.hpp"
#include "shared/campaign_score.hpp"

void __fastcall unknown_set_dialog_item_number_467240(HWND dialog, int id, int value)
{
    wchar_t text[32];
    swprintf(text, L"%d", value);
    HWND item = GetDlgItem(dialog, id);
    SendMessageA(item, 0x4b2, 0, (long)text);
}
