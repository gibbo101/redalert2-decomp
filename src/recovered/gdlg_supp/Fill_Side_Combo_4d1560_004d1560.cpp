// void __fastcall Fill_Side_Combo_4d1560(HWND dialog, int id) (0x004D1560)
// Fills a side combo box: "GUI:RandomEx" (item data -2), then every
// multiplayer house type (data: its index), and selects the first item. The
// box is hidden while it is filled when it was visible.
#include "shared/gdlg_supp.hpp"
#include "shared/house_type.hpp"
#include "shared/string_table.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?HouseTypes@@3V?$DynamicVectorClass@PAVHouseTypeClass@@@@A=00a35d08
// @ref ??_C@_0N@IEED@GUI?3RandomEx?$AA@=007d8640

void __fastcall Fill_Side_Combo_4d1560(HWND dialog, int id)
{
    HWND combo = GetDlgItem(dialog, id);
    bool hidden = ShowWindow(combo, SW_HIDE) == 0;
    SendMessageA(combo, CB_RESETCONTENT, 0, 0);
    SendMessageA(combo, 0x4DE, 0, 7);
    int item = SendMessageA(combo, 0x4C2, 0, (LPARAM)StringTable::Load_String("GUI:RandomEx", 0, "D:\\Ra2\\GDlgSupp.cpp", 268));
    SendMessageA(combo, CB_SETITEMDATA, item, -2);
    int count = HouseTypes.Count();
    for (int index = 0; index < count; index++) {
        HouseTypeClass *type = HouseTypes[index];
        if (type->Multiplay) {
            const unsigned short *name = type->UIName;
            item = SendMessageA(combo, 0x4C2, 0, (LPARAM)name);
            SendMessageA(combo, CB_SETITEMDATA, item, index);
        }
    }
    SendMessageA(combo, 0x4F1, 0, 0);
    SendMessageA(combo, CB_SETCURSEL, 0, 0);
    if (!hidden) {
        ShowWindow(combo, SW_SHOW);
    }
}
