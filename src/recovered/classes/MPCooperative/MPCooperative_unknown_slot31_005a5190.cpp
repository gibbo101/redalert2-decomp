// void MPCooperative::unknown_slot31() -- 0x005A5190
// Makes and loads the campaign on first use and names it after the two players; when a saved
// campaign exists, offers it: in the campaign dialog (0x6B) adds a "use the save" row for the saved
// map to the lobby list once, elsewhere prints that a saved campaign is available.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref __stricmp=00781f20
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ?Set_Names@CoopCampaignClass@@QAEXPBG0@Z=0048e190
// @ref ??_C@_0BC@DFJB@D?3?2Ra2?2MPCoop?4cpp?$AA@=007e34e4
// @ref ??_C@_04OANC@?4MAP?$AA@=007e375c
// @ref ??_C@_0BC@IPCP@TXT_COOP_USE_SAVE?$AA@=007e3748
// @ref ??_C@_0BI@MBLD@TXT_SAVE_CAMP_AVAILABLE?$AA@=007e379c
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/multi_mission.hpp"
#include "shared/string_table.hpp"
#include "shared/lobby.hpp"
#include "shared/wol_sink.hpp"
#include "shared/win32_api.hpp"
#include "shared/crt_string.hpp"

void MPCooperative::unknown_slot31()
{
    if (unknown_campaign_44 == 0) {
        unknown_campaign_44 = new CoopCampaignClass();
        unknown_campaign_44->Load_Campaign_0048f590(0);
    }
    if (unknown_campaign_44 != 0) {
        if (unknown_players_a3fa7c.Count() == 2) {
            unknown_campaign_44->Set_Names(unknown_players_a3fa7c[0]->Name, unknown_players_a3fa7c[1]->Name);
        }
        unknown_slot20();
        if (unknown_campaign_44->Has_Saved_Campaign_0048fbf0()) {
            if (Current_Dialog_Id_00735b20() == 0x6B) {
                if (!unknown_4d) {
                    char name[260];
                    unknown_campaign_44->Saved_Map_Is_Undefined_0048fe70(name);
                    strcat(name, ".MAP");
                    MultiMission *map = 0;
                    int count = unknown_multi_missions_a3d8d8.Count();
                    for (int i = 0; i < count; i++) {
                        if (map != 0) {
                            break;
                        }
                        char const *scenario = unknown_multi_missions_a3d8d8[i]->unknown_58;
                        if (_stricmp(scenario, name) == 0) {
                            map = unknown_multi_missions_a3d8d8[i];
                        }
                    }
                    if (map != 0) {
                        HWND list = GetDlgItem(Unknown_00735B10(), 0x553);
                        int rows = SendMessageA(list, 0x18B, 0, 0);
                        if (rows != -1) {
                            SendMessageA(list, 0x4CD, 0, (LPARAM)StringTable::Load_String("TXT_COOP_USE_SAVE", 0, "D:\\Ra2\\MPCoop.cpp", 0x5E1));
                            SendMessageA(list, 0x19A, rows, (LPARAM)map);
                            unknown_4d = true;
                        }
                    }
                }
            } else {
                Unknown_005C2C80(-1, StringTable::Load_String("TXT_SAVE_CAMP_AVAILABLE", 0, "D:\\Ra2\\MPCoop.cpp", 0x5E7));
            }
        }
    }
}
