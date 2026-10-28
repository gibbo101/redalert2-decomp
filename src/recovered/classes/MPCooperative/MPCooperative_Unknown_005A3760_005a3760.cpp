// void MPCooperative::Unknown_005A3760(HWND dialog) -- 0x005A3760
// Fills each player row's side combo from the selected campaign record: "random" when the
// record lists more than one country, else its only country; then refreshes the rows and shows
// the campaign description (NAME:COOPDESC<n>) in the lobby.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref __imp__InvalidateRect@12=0079a494
// @ref ?Get_Lobby_Dialog_005c2c40@@YAPAUHWND__@@XZ=005c2c40
// @ref ?Unknown_005A3650@MPCooperative@@QAEXPAUHWND__@@H@Z=005a3650
// @ref ?Unknown_005cb170@@YIXPAUHWND__@@H@Z=005cb170
// @ref ?unknown_int_a3db1c@@3HA=00a3db1c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ShowWindow@8=0079a498
// @ref ??_C@_0BA@FFI@NAME?3COOPDESC?$CFd?$AA@=007e34f8
// @ref ??_C@_0BC@DFJB@D?3?2Ra2?2MPCoop?4cpp?$AA@=007e34e4
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/string_table.hpp"
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/house_type.hpp"

void MPCooperative::Unknown_005A3760(HWND dialog)
{
    if (dialog != 0) {
        int count = unknown_int_a3db1c;
        UnknownDescriptionRecord_00490E00 *record;
        unknown_campaigns_40->Get_Record_00490C50(unknown_340, &record);
        if (record != 0) {
            int players = record->Players.Count();
            if (players != 0) {
                for (int i = 0; i < count; i++) {
                    int id = Player_Side_Combo_ID_4d1350(i);
                    Unknown_005A3650(dialog, id);
                    if (players > 1) {
                        Select_Side_Combo_4d1a90(dialog, id, -2);
                        unknown_player_slots_a3fa98[i]->unknown_66e2d0(-2);
                    } else {
                        int house = Find_Country_Index_004904A0(record->Players[0]);
                        Select_Side_Combo_4d1a90(dialog, id, house);
                        unknown_player_slots_a3fa98[i]->unknown_66e2d0(house);
                    }
                }
                Unknown_005cb170(dialog, count);
                HWND lobby = Get_Lobby_Dialog_005c2c40();
                int campaign;
                if (lobby != 0 && unknown_campaign_44 != 0 && unknown_campaign_44->Get_Campaign_Type_0048e6b0(&campaign)) {
                    char label[64];
                    sprintf(label, "NAME:COOPDESC%d", campaign + 1);
                    HWND item = GetDlgItem(lobby, 0x72F);
                    if (item != 0) {
                        SendMessageA(item, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\MPCoop.cpp", 0x273));
                        ShowWindow(item, SW_SHOW);
                        InvalidateRect(item, 0, 0);
                    }
                }
            }
        }
    }
}
