// void __fastcall Fill_Observer_Combo_4d1640(HWND dialog, int id) (0x004D1640)
// Fills a side combo box with "GUI:Observer" alone (item data -3) and
// selects it; hidden while filled when it was visible.
#include "shared/gdlg_supp.hpp"
#include "shared/string_table.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ??_C@_0N@JEHJ@GUI?3Observer?$AA@=007d8650

void __fastcall Fill_Observer_Combo_4d1640(HWND dialog, int id)
{
    HWND combo = GetDlgItem(dialog, id);
    bool hidden = ShowWindow(combo, SW_HIDE) == 0;
    SendMessageA(combo, CB_RESETCONTENT, 0, 0);
    SendMessageA(combo, 0x4DE, 0, 7);
    int item = SendMessageA(combo, 0x4C2, 0, (LPARAM)StringTable::Load_String("GUI:Observer", 0, "D:\\Ra2\\GDlgSupp.cpp", 298));
    SendMessageA(combo, CB_SETITEMDATA, item, -3);
    SendMessageA(combo, CB_SETCURSEL, 0, 0);
    SendMessageA(combo, 0x4F1, 0, 1);
    if (!hidden) {
        ShowWindow(combo, SW_SHOW);
    }
}
