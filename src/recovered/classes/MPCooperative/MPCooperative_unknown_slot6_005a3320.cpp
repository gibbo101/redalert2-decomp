// bool MPCooperative::unknown_slot6() -- 0x005A3320
// Loads the campaign selected in the lobby list (the saved campaign past the last record), then
// refreshes the side combos and resets the country of every player slot 7 refuses.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref ?Get_Lobby_Dialog_005c2c40@@YAPAUHWND__@@XZ=005c2c40
// @ref ?Selected_Campaign_005c67a0@@YAHXZ=005c67a0
// @ref ?Current_Dialog_Id_00735b20@@YAHXZ=00735b20
// @ref ?Unknown_005A3760@MPCooperative@@QAEXPAUHWND__@@@Z=005a3760
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"

bool MPCooperative::unknown_slot6()
{
    if (unknown_campaigns_40 == 0 || unknown_campaign_44 == 0) {
        return false;
    }
    int count;
    unknown_campaigns_40->Get_Count_00490C90(&count);
    int selected = Selected_Campaign_005c67a0();
    if (selected >= count) {
        if (unknown_players_a3fa7c.Count() == 2) {
            unknown_campaign_44->Set_Names(unknown_players_a3fa7c[0]->Name, unknown_players_a3fa7c[1]->Name);
        }
        if (!unknown_campaign_44->Load_Saved_Campaign_0048eb30()) {
            return false;
        }
        unknown_4c = true;
    } else if (Current_Dialog_Id_00735b20() == 0x6B) {
        delete unknown_campaign_44;
        unknown_campaign_44 = unknown_campaigns_328[selected];
        unknown_campaigns_328[selected] = new CoopCampaignClass();
        unknown_campaigns_328[selected]->Load_Campaign_0048f590(selected);
        unknown_50 = selected;
        if (unknown_players_a3fa7c.Count() == 2) {
            unknown_campaign_44->Set_Names(unknown_players_a3fa7c[0]->Name, unknown_players_a3fa7c[1]->Name);
        }
    }
    UnknownDescriptionRecord_00490E00 *record;
    unknown_campaigns_40->Get_Record_00490C50(unknown_340, &record);
    if (record == 0) {
        return false;
    }
    int players = record->Players.Count();
    if (players == 0) {
        return false;
    }
    Unknown_005A3760(Get_Lobby_Dialog_005c2c40());
    for (int i = 0; i < unknown_players_a3fa7c.Count(); i++) {
        if (!unknown_slot7(unknown_players_a3fa7c[i]->unknown_66e290())) {
            if (players > 1) {
                unknown_players_a3fa7c[i]->unknown_66e2d0(-2);
            } else {
                int house = Find_Country_Index_004904A0(record->Players[0]);
                unknown_players_a3fa7c[i]->unknown_66e2d0(house);
            }
        }
    }
    return true;
}
