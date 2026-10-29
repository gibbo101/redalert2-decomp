// void MPCooperative::unknown_slot30() -- 0x005A5000
// In the campaign dialog (0x6B) drops the lobby list's last row once; elsewhere reloads the chosen
// campaign and selects its current map, refreshes the lobby dialog and sends the lobby state. Then
// clears the campaign's player names.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref _sprintf=007820f4
// @ref __stricmp=00781f20
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ?Set_Names@CoopCampaignClass@@QAEXPBG0@Z=0048e190
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ??_C@_06HIDC@?$CFs?4MAP?$AA@=007e3794
// @ref ?Unknown_005c3450@@YIXPAUHWND__@@PAVMultiplayerGameMode@@@Z=005c3450
// @ref ?Unknown_005c34b0@@YIXPAUHWND__@@@Z=005c34b0
// @ref ?Unknown_005c7570@@YIXPAUHWND__@@@Z=005c7570
// @ref ?Unknown_005c3810@@YIX_N0@Z=005c3810
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/id_source.hpp"
#include "shared/multi_mission.hpp"
#include "shared/lobby.hpp"
#include "shared/wol_sink.hpp"
#include "shared/abstract_type.hpp"
#include "shared/win32_api.hpp"
#include "shared/crt_string.hpp"
#include "shared/session_state.hpp"

void MPCooperative::unknown_slot30()
{
    if (Current_Dialog_Id_00735b20() == 0x6B) {
        if (unknown_4d) {
            HWND list = GetDlgItem(Unknown_00735B10(), 0x553);
            int count = SendMessageA(list, 0x18B, 0, 0);
            if (count == -1) {
                if (unknown_campaign_44 != 0) {
                    unknown_campaign_44->Set_Names(unknown_empty_wide_839d4c, unknown_empty_wide_839d4c);
                }
                return;
            }
            if (SendMessageA(list, 0x188, 0, 0) == count - 1) {
                SendMessageA(list, 0x186, count - 2, 0);
            }
            SendMessageA(list, 0x182, count - 1, 0);
            unknown_4d = false;
        }
    } else {
        if (unknown_campaign_44 != 0 && unknown_4c) {
            if (unknown_50 != 0) {
                unknown_campaign_44->Load_Campaign_0048f590(0);
                unknown_campaign_44->Load_Campaign_0048f590(unknown_50);
            } else {
                unknown_campaign_44->Load_Campaign_0048f590(1);
                unknown_campaign_44->Load_Campaign_0048f590(unknown_50);
            }
            char *map;
            unknown_campaign_44->Get_Map_Name_0048fb40(&map, -1);
            int count = unknown_multi_missions_a3d8d8.Count();
            char name[260];
            sprintf(name, "%s.MAP", map);
            int i;
            for (i = 0; i < count; i++) {
                char const *scenario = unknown_multi_missions_a3d8d8[i]->unknown_58;
                if (_stricmp(scenario, name) == 0) {
                    break;
                }
            }
            unknown_session_a3d298.ScenarioIndex = i;
            unknown_id_source_a3d290->TechLevel = i;
            Select_Scenario_005c7c30(i);
        }
        HWND dialog = Get_Lobby_Dialog_005c2c40();
        if (dialog != 0) {
            Unknown_005c3450(dialog, this);
            Unknown_005c34b0(dialog);
            Unknown_005c7570(dialog);
        }
        Unknown_005c3810(true, true);
    }
    if (unknown_campaign_44 != 0) {
        unknown_campaign_44->Set_Names(unknown_empty_wide_839d4c, unknown_empty_wide_839d4c);
    }
}
