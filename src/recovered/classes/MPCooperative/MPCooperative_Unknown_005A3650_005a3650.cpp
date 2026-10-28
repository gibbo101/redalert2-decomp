// void MPCooperative::Unknown_005A3650(HWND dialog, int id) -- 0x005A3650
// Refills one side combo with the countries the selected campaign record lists ("random" first when
// it lists more than one), each with its HouseTypes index as item data.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ShowWindow@8=0079a498
// @ref ?HouseTypes@@3V?$DynamicVectorClass@PAVHouseTypeClass@@@@A=00a35d08
// @ref ??_C@_0L@KAA@GUI?3Random?$AA@=007e353c
// @ref ??_C@_0BC@DFJB@D?3?2Ra2?2MPCoop?4cpp?$AA@=007e34e4
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/string_table.hpp"
#include "shared/house_type.hpp"

void MPCooperative::Unknown_005A3650(HWND dialog, int id)
{
    int count = HouseTypes.Count();
    if (count != 0) {
        HWND combo = GetDlgItem(dialog, id);
        ShowWindow(combo, SW_HIDE);
        SendMessageA(combo, 0x14B, 0, 0);
        UnknownDescriptionRecord_00490E00 *record;
        unknown_campaigns_40->Get_Record_00490C50(unknown_340, &record);
        if (record != 0) {
            int players = record->Players.Count();
            if (players != 0) {
                if (players > 1) {
                    wchar_t const *name = StringTable::Load_String("GUI:Random", 0, "D:\\Ra2\\MPCoop.cpp", 0x225);
                    LRESULT index = SendMessageA(combo, 0x4C2, 0, (LPARAM)name);
                    SendMessageA(combo, 0x151, index, -2);
                }
                for (int i = 0; i < players; i++) {
                    int house = Find_Country_Index_004904A0(record->Players[i]);
                    if (house >= 0 && house < count) {
                        wchar_t const *name = HouseTypes[house]->UIName;
                        LRESULT index = SendMessageA(combo, 0x4C2, 0, (LPARAM)name);
                        SendMessageA(combo, 0x151, index, house);
                    }
                }
                SendMessageA(combo, 0x14E, 0, 0);
                ShowWindow(combo, SW_SHOW);
            }
        }
    }
}
