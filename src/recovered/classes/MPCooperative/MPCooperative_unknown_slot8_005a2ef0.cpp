// void MPCooperative::unknown_slot8() -- 0x005A2EF0
// Lobby set-up: drops the campaign when the lobby's map no longer belongs to it, makes and loads
// the campaign for the map (selecting the campaign's first map when the session's map is not one
// of its records), then refreshes the side combos and the campaign description.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref __strnicmp=007858d0
// @ref ?Unknown_005A2E50@MPCooperative@@QAEHXZ=005a2e50
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ShowWindow@8=0079a498
// @ref ?unknown_lobby_flag_7e6d90@@3HA=007e6d90
// @ref ?Send_Game_Options_005c3c60@@YIXPBD@Z=005c3c60
// @ref ?Select_Scenario_005c7c30@@YI_NH@Z=005c7c30
// @ref ?Get_Lobby_Dialog_005c2c40@@YAPAUHWND__@@XZ=005c2c40
// @ref ?Current_Dialog_Id_00735b20@@YAHXZ=00735b20
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ??_C@_0BL@OAOD@Sending?5observer?5slot?5of?58?$AA@=007e3520
// @ref ??_C@_02NBIM@O8?$AA@=007e351c
// @ref ??_C@_0BD@HCAC@?$EA?$EA?$EA?5Looking?5for?5?$CFs?$AA@=007e3508
// @ref ??_C@_0BA@FFI@NAME?3COOPDESC?$CFd?$AA@=007e34f8
// @ref ??_C@_0BC@DFJB@D?3?2Ra2?2MPCoop?4cpp?$AA@=007e34e4
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/string_table.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/multi_mission.hpp"
#include "shared/abstract_type.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_tokens.hpp"

void MPCooperative::unknown_slot8()
{
    if (unknown_campaigns_40 == 0) {
        return;
    }
    unknown_lobby_flag_7e6d90 = -1;
    Debug_Printf("Sending observer slot of 8");
    Send_Game_Options_005c3c60("O8");
    if (Find_Dialog_00735940(0xC2) != 0 || Find_Dialog_00735940(0xBC) != 0) {
        if (unknown_campaign_44 != 0) {
            int type;
            unknown_campaign_44->Get_Campaign_Type_0048e6b0(&type);
            if ((Unknown_005A2E50() != type && Current_Dialog_Id_00735b20() == 0x6B) || Current_Dialog_Id_00735b20() != 0x6B) {
                delete unknown_campaign_44;
                unknown_campaign_44 = 0;
            }
        }
        if (unknown_campaign_44 != 0) {
            if (unknown_players_a3fa7c.Count() == 2) {
                unknown_campaign_44->Set_Names(unknown_players_a3fa7c[0]->Name, unknown_players_a3fa7c[1]->Name);
            } else {
                unknown_campaign_44->Set_Names(unknown_empty_wide_839d4c, unknown_empty_wide_839d4c);
            }
        }
    }
    if (unknown_campaign_44 == 0) {
        unknown_campaign_44 = new CoopCampaignClass();
        if (unknown_campaign_44 == 0) {
            return;
        }
        unknown_campaign_44->Load_Campaign_0048f590(0);
        int index = Unknown_005A2E50();
        if (index < 0) {
            unknown_340 = 0;
            char *name = 0;
            unknown_campaign_44->Get_Map_Name_0048fb40(&name, 0);
            int i;
            for (i = 0; i < unknown_multi_missions_a3d8d8.Count(); i++) {
                char const *scenario = unknown_multi_missions_a3d8d8[i]->unknown_58;
                if (_strnicmp(scenario, name, strlen(name)) == 0) {
                    unknown_session_a3d298.ScenarioIndex = i;
                    Select_Scenario_005c7c30(i);
                    break;
                }
            }
            if (i == unknown_multi_missions_a3d8d8.Count()) {
                unknown_session_a3d298.ScenarioIndex = 0;
                Select_Scenario_005c7c30(0);
            }
        } else {
            unknown_340 = index;
            UnknownDescriptionRecord_00490E00 *record;
            unknown_campaigns_40->Get_Record_00490C50(index, &record);
            char *name = 0;
            unknown_campaign_44->Get_Map_Name_0048fb40(&name, 0);
            Debug_Printf("@@@ Looking for %s", unknown_multi_missions_a3d8d8[unknown_session_a3d298.ScenarioIndex]->unknown_58);
            char const *scenario = unknown_multi_missions_a3d8d8[unknown_session_a3d298.ScenarioIndex]->unknown_58;
            if (_strnicmp(scenario, name, strlen(name)) != 0) {
                int other = index == 0;
                do {
                    unknown_campaign_44->Load_Campaign_0048f590(other);
                    unknown_campaign_44->Load_Campaign_0048f590(index);
                    unknown_campaign_44->Get_Map_Name_0048fb40(&name, 0);
                    scenario = unknown_multi_missions_a3d8d8[unknown_session_a3d298.ScenarioIndex]->unknown_58;
                } while (_strnicmp(scenario, name, strlen(name)) != 0);
            }
        }
    }
    unknown_344 = true;
    int campaign;
    HWND lobby = Get_Lobby_Dialog_005c2c40();
    if (lobby != 0) {
        Unknown_005A3760(lobby);
        HWND item = GetDlgItem(lobby, 0x72F);
        if (item != 0 && unknown_campaign_44 != 0 && unknown_campaign_44->Get_Campaign_Type_0048e6b0(&campaign)) {
            char label[64];
            sprintf(label, "NAME:COOPDESC%d", campaign + 1);
            SendMessageA(item, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\MPCoop.cpp", 0x157));
            ShowWindow(item, SW_SHOW);
        }
    }
}
