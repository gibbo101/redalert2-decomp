// void __fastcall Fill_Random_Color_Combo_4d2250(HWND dialog, int id) (0x004D2250)
// Fills a colour combo box with "GUI:RandomAsSymbols" alone (item data -2)
// and selects it; hidden while it is filled when it was visible.
#include "shared/gdlg_supp.hpp"
#include "shared/string_table.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??_C@_0BE@MIDK@GUI?3RandomAsSymbols?$AA@=007d87dc

void __fastcall Fill_Random_Color_Combo_4d2250(HWND dialog, int id)
{
    HWND combo = GetDlgItem(dialog, id);
    bool hidden = ShowWindow(combo, SW_HIDE) == 0;
    SendMessageA(combo, CB_RESETCONTENT, 0, 0);
    SendMessageA(combo, 0x4DD, 0, 1);
    SendMessageA(combo, 0x4DE, 0, 9);
    int item = SendMessageA(combo, 0x4C2, 0, (LPARAM)StringTable::Load_String("GUI:RandomAsSymbols", 0, "D:\\Ra2\\GDlgSupp.cpp", 544));
    SendMessageA(combo, CB_SETITEMDATA, item, -2);
    SendMessageA(combo, 0x498, item, -1);
    SendMessageA(combo, CB_SETCURSEL, 0, 0);
    SendMessageA(combo, 0x4F1, 0, 1);
    if (!hidden) {
        ShowWindow(combo, SW_SHOW);
    }
}
