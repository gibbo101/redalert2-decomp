// void MPCooperative::unknown_slot34(bool player_wins) -- 0x005A46C0
// The end of a cooperative map: when a human player is still in, advances and saves the campaign
// (announcing the result), marks the scenario to skip its score and map selection, saves the
// session's players into unknown_players_5c (unknown_58: the local one's row) and the session
// settings into +0x74..+0x1A8 for slot 37, and resets the per-game state.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
// @ref _wcscpy=00783689
// @ref __real@8@4008e100000000000000=0079b608
// @ref ??_C@_0BC@DFJB@D?3?2Ra2?2MPCoop?4cpp?$AA@=007e34e4
// @ref ??_C@_0BF@KKKM@TXT_COOP_SAVE_FAILED?$AA@=007e36ec
// @ref ??_C@_0BG@HJAK@TXT_COOP_SAVE_SUCCESS?$AA@=007e3704
// @ref ??_C@_0CJ@IEBL@?$EA?$EA?$EA?$EA?5End?9of?9Game?3?5PlayerWins?3?$CFd?0@=007e371c
// @ref ?unknown_833680@@3HA=00833680
// @ref ?unknown_833684@@3HA=00833684
// @ref ?unknown_833688@@3HA=00833688
// @ref ?unknown_address_a3db2c@@3VIPXAddressClass@@A=00a3db2c
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/house.hpp"
#include "shared/id_source.hpp"
#include "shared/rules.hpp"
#include "shared/string_table.hpp"
#include "shared/uicmnds.hpp"
#include "shared/gadget.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"

extern int unknown_833680;    // 0x00833680
extern int unknown_833684;    // 0x00833684
extern int unknown_833688;    // 0x00833688

void MPCooperative::unknown_slot34(bool player_wins)
{
    bool win = false;
    for (int i = 0; i < Houses.Count(); i++) {
        if (Houses[i] != 0 && Houses[i]->unknown_func_4f52f0() && !Houses[i]->unknown_13d) {
            win = true;
        }
    }
    Debug_Printf("@@@@ End-of-Game: PlayerWins:%d, win:%d\n", player_wins, win);
    if (win) {
        int scheme = Gadget_Color_Scheme();
        if (unknown_campaign_44 != 0) {
            unknown_campaign_44->Next_Map_0048e360();
            if (unknown_campaign_44->Save_Campaign_0048f040()) {
                unknown_messages_a3dc70.Add_Message(0, 0, StringTable::Load_String("TXT_COOP_SAVE_SUCCESS", 0, "D:\\Ra2\\MPCoop.cpp", 0x42E),
                    scheme, 0x16, (int)(Rules->MessageDelay * 900.0), 0);
            } else {
                unknown_messages_a3dc70.Add_Message(0, 0, StringTable::Load_String("TXT_COOP_SAVE_FAILED", 0, "D:\\Ra2\\MPCoop.cpp", 0x430),
                    scheme, 0x16, (int)(Rules->MessageDelay * 900.0), 0);
            }
        }
    }
    wcscpy(unknown_host_name_78, unknown_session_a3d298.HostName_2380);
    unknown_id_source_a3d290->SkipScore = true;
    unknown_id_source_a3d290->EndOfGame = false;
    unknown_id_source_a3d290->SkipMapSelect = true;
    unknown_id_source_a3d290->OneTimeOnly = false;
    Free_Pointers_005a7480(&unknown_players_5c);
    unknown_58 = 0;
    for (int p = 0; p < unknown_players_a3fa7c.Count(); p++) {
        NodeNameType *entry = new NodeNameType;
        wcscpy(entry->Name, unknown_players_a3fa7c[p]->Name);
        entry->unknown_6b = unknown_players_a3fa7c[p]->unknown_6b;
        entry->unknown_4b = unknown_players_a3fa7c[p]->unknown_4b;
        entry->unknown_53 = unknown_players_a3fa7c[p]->unknown_53;
        entry->ID = unknown_players_a3fa7c[p]->ID;
        strcpy(entry->unknown_34, unknown_players_a3fa7c[p]->unknown_34);
        entry->unknown_4f = unknown_players_a3fa7c[p]->unknown_4f;
        entry->unknown_57 = unknown_players_a3fa7c[p]->unknown_57;
        entry->Team = unknown_players_a3fa7c[p]->Team;
        entry->unknown_63 = unknown_players_a3fa7c[p]->unknown_63;
        entry->unknown_67 = unknown_players_a3fa7c[p]->unknown_67;
        entry->unknown_6b = unknown_players_a3fa7c[p]->unknown_6b;
        entry->Address = unknown_players_a3fa7c[p]->Address;
        unknown_players_5c.Add(entry);
        if (unknown_address_a3db2c == unknown_players_a3fa7c[p]->Address) {
            unknown_58 = p;
        }
    }
    unknown_c8 = unknown_session_a3d298.unknown_293c;
    unknown_128 = unknown_session_a3d298.unknown_299c;
    unknown_148 = unknown_session_a3d298.unknown_2fa0;
    unknown_198 = unknown_session_a3d298.unknown_3022;
    wcscpy(unknown_master_name_168, unknown_session_a3d298.MasterPlayerName);
    unknown_master_id_194 = unknown_session_a3d298.MasterPlayerID;
    unknown_74 = unknown_session_a3d298.unknown_124;
    unknown_a0 = unknown_session_a3d298.unknown_3aa4;
    unknown_a4 = unknown_house_setting_7d88d8;
    unknown_units_a8 = unknown_session_a3d298.UnitCount;
    unknown_credits_ac = unknown_session_a3d298.unknown_24;
    unknown_fog_b0 = unknown_session_a3d298.unknown_fog_a7;
    unknown_b1 = unknown_session_a3d298.unknown_28;
    unknown_crates_b2 = unknown_session_a3d298.unknown_crates_29;
    unknown_b3 = unknown_session_a3d298.unknown_a8;
    unknown_b4 = unknown_session_a3d298.unknown_a4;
    unknown_b5 = unknown_session_a3d298.unknown_a5;
    unknown_bases_b6 = unknown_session_a3d298.unknown_bases_20;
    unknown_b7 = unknown_session_a3d298.unknown_a6;
    unknown_ai_count_b8 = unknown_session_a3d298.AICount;
    unknown_difficulty_bc = unknown_session_a3d298.unknown_difficulty_40;
    unknown_c0 = unknown_session_a3d298.unknown_2a;
    unknown_c1 = unknown_session_a3d298.unknown_2b;
    unknown_c2 = unknown_session_a3d298.unknown_2c;
    unknown_c3 = unknown_session_a3d298.unknown_34;
    unknown_game_speed_c4 = unknown_session_a3d298.GameSpeed_30;
    unknown_session_a3d298.unknown_2b0 = 0;
    Map.Unknown_00498F10(0);
    unknown_833680 = 0;
    unknown_833684 = 0;
    unknown_833688 = -1;
    for (int row = 0; row < 4; row++) {
        unknown_session_a3d298.unknown_1fb4[row][unknown_session_a3d298.unknown_2300] = -1;
    }
}
