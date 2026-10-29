// void MPCooperative::unknown_slot37() -- 0x005A5720
// The next cooperative map: points the scenario at the campaign's current map, restores the
// session's players and settings slot 34 saved, sets the computer players from the campaign
// record, restarts the network timing from the players' pings and drops the connections.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
// @ref _wcscpy=00783689
// @ref _strncmp=00783810
// @ref _sprintf=007820f4
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ??_C@_0BA@FOMN@xxx?4xxx?4xxx?4xxx?$AA@=007e38d0
// @ref ??_C@_04IOAL@Hard?$AA@=007ceadc
// @ref ??_C@_06BILL@Normal?$AA@=007d1b30
// @ref ??_C@_06HIDC@?$CFs?4MAP?$AA@=007e3794
// @ref ??_C@_0BD@LFFN@Max?5ping?5is?5?$CFd?5ms?6?$AA@=007e38bc
// @ref ??_C@_0BK@HFDA@Ping?5times?5not?5available?6?$AA@=007e38a0
// @ref ??_C@_0DI@DFCB@?$EA?$EA?$EA?$EA?5After?5destroying?5connection@=007e382c
// @ref ??_C@_0DJ@PLDA@?$EA?$EA?$EA?$EA?5Before?5destroying?5connectio@=007e3864
// @ref ?Unknown_0063FC90@OwnerTalkClass@@QAEXXZ=0063fc90
// @ref ?unknown_address_a3db2c@@3VIPXAddressClass@@A=00a3db2c
// @ref ?unknown_b293d8@@3_NA=00b293d8
// @ref ?unknown_b2a6d8@@3PADA=00b2a6d8
// @ref ?unknown_b2a820@@3_NA=00b2a820
// @ref ?unknown_b2ab84@@3IA=00b2ab84
// @ref ?DoList@@3V?$QueueClass@VEventClass@@$0EAAA@@@A=00866270
// @ref ?unknown_pings_b2a734@@3PAHA=00b2a734
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/id_source.hpp"
#include "shared/multi_mission.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/network_statistics.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/connection.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/owner_talk.hpp"
#include "shared/options.hpp"
#include "shared/tool_tip.hpp"
#include "shared/gscreen.hpp"
#include "shared/wol_sink.hpp"
#include "shared/event.hpp"
#include "shared/wstring.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"

extern "C" int __cdecl strncmp(char const *left, char const *right, unsigned int count);
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
extern Wstring unknown_wstring_b26cb8;
extern unsigned int unknown_protocol_7fd370;
extern char unknown_b2a6d8[];
extern unsigned int unknown_b2ab84;
extern int unknown_pings_b2a734[];
extern bool unknown_b2a820;
extern bool unknown_b293d8;
extern IPXManagerClass unknown_ipx_manager_a40978;
extern OwnerTalkClass unknown_OwnerTalkClass_00ab6d18;
void Unknown_Pregame_Setup_005c74f0();
extern CCToolTip *ToolTips;

void MPCooperative::unknown_slot37()
{
    NetNumType net;
    NetNodeType node;
    unsigned short port;
    char *map;
    unknown_campaign_44->Get_Map_Name_0048fb40(&map, -1);
    char name[260];
    sprintf(name, "%s.MAP", map);
    strcpy(unknown_id_source_a3d290->NextScenario, name);
    unknown_id_source_a3d290->unknown_224c = -1;
    unknown_id_source_a3d290->SkipScore = true;
    int count = unknown_multi_missions_a3d8d8.Count();
    sprintf(name, "%s.MAP", map);
    for (int i = 0; i < count; i++) {
        if (strncmp(name, unknown_multi_missions_a3d8d8[i]->unknown_58, 0x104) == 0) {
            unknown_session_a3d298.ScenarioIndex = i;
            break;
        }
    }
    unknown_b2a7fc = 0;
    unknown_b2ab84 = unknown_protocol_7fd370;
    unknown_b2a7ec = 0;
    strcpy(unknown_b2a6d8, unknown_wstring_b26cb8.Get());
    wcscpy(unknown_session_a3d298.HostName_2380, unknown_host_name_78);
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
    unknown_session_a3d55c = 0;
    for (int p = 0; p < unknown_players_5c.Count(); p++) {
        NodeNameType *entry = new NodeNameType;
        wcscpy(entry->Name, unknown_players_5c[p]->Name);
        entry->unknown_6b = unknown_players_5c[p]->unknown_6b;
        entry->unknown_4b = unknown_players_5c[p]->unknown_4b;
        entry->unknown_53 = unknown_players_5c[p]->unknown_53;
        entry->ID = unknown_players_5c[p]->ID;
        strcpy(entry->unknown_34, unknown_players_5c[p]->unknown_34);
        entry->unknown_4f = unknown_players_5c[p]->unknown_4f;
        entry->unknown_57 = unknown_players_5c[p]->unknown_57;
        entry->Team = unknown_players_5c[p]->Team;
        entry->unknown_63 = unknown_players_5c[p]->unknown_63;
        entry->unknown_67 = unknown_players_5c[p]->unknown_67;
        entry->unknown_6b = unknown_players_5c[p]->unknown_6b;
        entry->Address = unknown_players_5c[p]->Address;
        unknown_players_a3fa7c.Add(entry);
        unknown_session_a3d55c++;
    }
    int computers = unknown_multi_missions_a3d8d8[unknown_session_a3d298.ScenarioIndex]->unknown_184 - 2;
    if (computers > 0) {
        unknown_session_a3d298.AICount = computers;
        int used = 0;
        UnknownDescriptionRecord_00490E00 *record;
        unknown_campaigns_40->Get_Record_00490C50(unknown_340, &record);
        int current;
        unknown_campaign_44->Get_Current_Map_0048e6f0(&current);
        for (int slot = 2; slot < 8; slot++) {
            if (used < computers) {
                if (strcmp(record->AIName, "Normal") == 0) {
                    unknown_session_a3d298.AIDifficulty[slot] = 1;
                } else if (strcmp(record->AIName, "Hard") == 0) {
                    unknown_session_a3d298.AIDifficulty[slot] = 0;
                } else {
                    unknown_session_a3d298.AIDifficulty[slot] = 2;
                }
                unknown_session_a3d298.AICountry[slot] = unknown_1a8[slot][current];
                unknown_session_a3d298.AIColor[slot] = unknown_268[slot][current];
                used++;
            } else {
                unknown_session_a3d298.AICountry[slot] = -1;
                unknown_session_a3d298.AIColor[slot] = -1;
            }
        }
    }
    unknown_address_a3db2c = unknown_players_a3fa7c[unknown_58]->Address;
    wcscpy(unknown_session_a3d298.MasterPlayerName, unknown_players_a3fa7c[unknown_58]->Name);
    unknown_session_a3d298.MasterPlayerID = -1;
    unknown_session_a3d298.unknown_124 = unknown_74;
    PacketTransport->unknown_slot12();
    char address[32] = "xxx.xxx.xxx.xxx";
    for (int n = 1; n < unknown_players_a3fa7c.Count(); n++) {
        unknown_players_a3fa7c[n]->Address.Get_Address(net, node, &port);
        PacketTransport->unknown_slot11(address, port);
    }
    unknown_session_a3d298.unknown_293c = unknown_c8;
    unknown_session_a3d298.unknown_299c = unknown_128;
    unknown_session_a3d298.unknown_2fa0 = unknown_148;
    unknown_session_a3d298.unknown_3022 = unknown_198;
    wcscpy(unknown_session_a3d298.MasterPlayerName, unknown_master_name_168);
    unknown_session_a3d298.MasterPlayerID = unknown_master_id_194;
    unknown_session_a3d298.unknown_3aa4 = unknown_a0;
    unknown_house_setting_7d88d8 = unknown_a4;
    unknown_session_a3d298.UnitCount = unknown_units_a8;
    unknown_session_a3d298.unknown_24 = unknown_credits_ac;
    unknown_session_a3d298.unknown_fog_a7 = unknown_fog_b0;
    unknown_session_a3d298.unknown_28 = unknown_b1;
    unknown_session_a3d298.unknown_crates_29 = unknown_crates_b2;
    unknown_session_a3d298.unknown_a8 = unknown_b3;
    unknown_session_a3d298.unknown_a4 = unknown_b4;
    unknown_session_a3d298.unknown_a5 = unknown_b5;
    unknown_session_a3d298.unknown_bases_20 = unknown_bases_b6;
    unknown_session_a3d298.unknown_a6 = unknown_b7;
    unknown_session_a3d298.unknown_difficulty_40 = unknown_difficulty_bc;
    unknown_session_a3d298.unknown_2a = unknown_c0;
    unknown_session_a3d298.unknown_2b = unknown_c1;
    unknown_session_a3d298.unknown_2c = unknown_c2;
    unknown_session_a3d298.unknown_34 = unknown_c3;
    unknown_session_a3d298.GameSpeed_30 = unknown_game_speed_c4;
    Select_Scenario_005c7c30(unknown_session_a3d298.ScenarioIndex);
    Options.GameSpeed = unknown_session_a3d298.GameSpeed_30;
    unknown_id_source_a3d290->TechLevel = unknown_session_a3d298.ScenarioIndex;
    switch (unknown_session_a3d298.GameSpeed_30) {
    case 0:
        unknown_session_a3d298.MaxAhead_2c8 = 40;
        unknown_session_a3d298.unknown_2e8 = 60;
        unknown_session_a3d298.unknown_2cc = 10;
        break;
    case 1:
        unknown_session_a3d298.MaxAhead_2c8 = 40;
        unknown_session_a3d298.unknown_2e8 = 45;
        unknown_session_a3d298.unknown_2cc = 10;
        break;
    case 2:
        unknown_session_a3d298.MaxAhead_2c8 = 30;
        unknown_session_a3d298.unknown_2e8 = 30;
        break;
    case 3:
        unknown_session_a3d298.MaxAhead_2c8 = 20;
        unknown_session_a3d298.unknown_2e8 = 20;
        break;
    case 4:
        unknown_session_a3d298.MaxAhead_2c8 = 20;
        unknown_session_a3d298.unknown_2e8 = 15;
        break;
    case 5:
        unknown_session_a3d298.MaxAhead_2c8 = 20;
        unknown_session_a3d298.unknown_2e8 = 12;
        break;
    default:
        unknown_session_a3d298.MaxAhead_2c8 = 10;
        unknown_session_a3d298.unknown_2e8 = 10;
        break;
    }
    unknown_session_a3d298.unknown_2e4 = 0;
    if (!unknown_04) {
        unknown_session_a3d298.unknown_2e8 = 0;
    }
    int ping = 0;
    for (int k = 0; k < unknown_players_a3fa7c.Count(); k++) {
        if (unknown_pings_b2a734[k] > ping) {
            ping = unknown_pings_b2a734[k];
        }
    }
    unknown_session_a3d298.unknown_290c = 1;
    if (ping == 0 || ping == 1000) {
        unknown_session_a3d298.unknown_2e8 = 0;
        Debug_Printf("Ping times not available\n");
    } else {
        Debug_Printf("Max ping is %d ms\n", ping);
        if (ping > 1000) {
            unknown_session_a3d298.unknown_290c = 2;
        } else if (ping < 600) {
            unknown_session_a3d298.unknown_290c = 1;
        }
        int retry = ping * 60 / 1000;
        retry += retry * 120 / 100;
        unknown_ipx_manager_a40978.Set_Timing(retry, -1, retry * 8, true);
        if (unknown_04) {
            unknown_ipx_manager_a40978.unknown_slot18(5, -1, 120);
            if (unknown_04) {
                switch (unknown_session_a3d298.unknown_290c) {
                case 0:
                case 1:
                    unknown_session_a3d298.unknown_2e4 = unknown_session_a3d298.MaxAhead_2c8;
                    break;
                case 2:
                    unknown_session_a3d298.unknown_2e4 = unknown_session_a3d298.MaxAhead_2c8 / 2 + unknown_session_a3d298.MaxAhead_2c8;
                    break;
                case 3:
                    unknown_session_a3d298.unknown_2e4 = unknown_session_a3d298.MaxAhead_2c8 * 2;
                    break;
                }
                unknown_session_a3d298.unknown_2e4 = unknown_session_a3d298.unknown_2e4 / 10 * 10;
            }
        }
    }
    unknown_session_a3d298.unknown_2e0 = unknown_session_a3d298.MaxAhead_2c8;
    memset(player_statistics_00a3d584, 0, sizeof(player_statistics_00a3d584));
    unknown_b2a820 = false;
    Options.GameSpeed = unknown_session_a3d298.GameSpeed_30;
    unknown_b293d8 = false;
    Unknown_Pregame_Setup_005c74f0();
    DoList.Count = 0;
    DoList.Head = 0;
    DoList.Tail = 0;
    OutList.Count = 0;
    OutList.Head = 0;
    OutList.Tail = 0;
    ToolTips->Enable(false);
    Debug_Printf("@@@@ Before destroying connections players.count() = %d\n", unknown_players_a3fa7c.Count());
    while (unknown_ipx_manager_a40978.Num_Connections()) {
        unknown_ipx_manager_a40978.Delete_Connection(unknown_ipx_manager_a40978.Connection_ID(0));
    }
    if (unknown_flag_a3fba8) {
        if (unknown_connection_a409c4) {
            unknown_OwnerTalkClass_00ab6d18.Unknown_0063FC90();
        }
        unknown_flag_a3fba8 = false;
    }
    Debug_Printf("@@@@ After destroying connections players.count() = %d\n", unknown_players_a3fa7c.Count());
}
