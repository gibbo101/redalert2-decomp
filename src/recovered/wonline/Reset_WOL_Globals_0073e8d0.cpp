// void Reset_WOL_Globals() (0x0073E8D0): puts every Westwood Online global back to its start state (wonline.cpp,
// the lobby names are lines 2485-2492). Called by Initialize_Wonline 0x00742390.
// Clear_Buddy_Lists groups the two string lists: both Clear calls stay out of line (0x007661C0) one level down.
// The Ladder and Channel node deletes are refused here and emit their ??_G bodies 0x00766780 and 0x007667E0.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"
#include "shared/modem_host.hpp"
#include "shared/player_profile.hpp"
extern rc_ptr<PlayerProfile> unknown_profile_ptr_b28cc0;
extern char wol_source_file_007fd62c[];
extern char wol_lobby_label_1_007fd7d0[],wol_lobby_label_2_007fd7c4[],wol_lobby_label_3_007fd7b8[],wol_lobby_label_4_007fd7ac[];
extern char wol_lobby_label_5_007fd7a0[],wol_lobby_label_6_007fd794[],wol_lobby_label_7_007fd788[],wol_lobby_label_8_007fd77c[];
extern HANDLE wol_wait_events_b264f8[18];
extern long unknown_b28ff4;
extern long unknown_b28ff8;
extern unsigned int unknown_b2a7f0;
extern unsigned int unknown_b26564;
extern int unknown_b26540[8];
extern int ladder_top_rung_b29ce8;
extern int wol_lan_leave_b2abf0;
extern int unknown_7fd300;
extern int unknown_time_b2abd0, unknown_time_b2abd4;
extern int unknown_b2ac2c,unknown_b2ab88;
extern long unknown_b2a8a4;
extern unsigned long wol_chat_cookie_b2ac60,wol_net_cookie_b2ac64,wol_download_cookie_b2ac68;
extern "C" long __cdecl time(long *);
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_lobby_label_1_007fd7d0@@3PADA=007fd7d0
// @ref ?wol_lobby_label_2_007fd7c4@@3PADA=007fd7c4
// @ref ?wol_lobby_label_3_007fd7b8@@3PADA=007fd7b8
// @ref ?wol_lobby_label_4_007fd7ac@@3PADA=007fd7ac
// @ref ?wol_lobby_label_5_007fd7a0@@3PADA=007fd7a0
// @ref ?wol_lobby_label_6_007fd794@@3PADA=007fd794
// @ref ?wol_lobby_label_7_007fd788@@3PADA=007fd788
// @ref ?wol_lobby_label_8_007fd77c@@3PADA=007fd77c
// @ref ?unknown_b28ff4@@3JA=00b28ff4
// @ref ?unknown_b28ff8@@3JA=00b28ff8
// @ref ?unknown_b2a7f0@@3IA=00b2a7f0
// @ref ?unknown_b26564@@3IA=00b26564
// @ref ?unknown_b26540@@3PAHA=00b26540
// @ref ?Read_Art_INI@@YIXXZ=00652730
// @ref ?unknown_art_ini_unique_id@@YAHXZ=00652710
// @ref ?unknown_ini_8397a0_unique_id@@YIHXZ=00652720
inline void Clear_Buddy_Lists()
{
    unknown_strings_b26920.Clear();
    unknown_strings_b29838.Clear();
}
template<class T> inline void Zero_Record(T &record) { memset(&record, 0, sizeof(record)); }
// @ref ?Set_Empty@WolIntArray@@QAEXXZ=00766060
// @ref ??_GNode@?$WolDictionary@VWstring@@ULadder@WOL@@@@QAEPAXI@Z=00766780
// @ref ??_GNode@?$WolDictionary@VWstring@@UChannel@WOL@@@@QAEPAXI@Z=007667e0
void __fastcall Reset_WOL_Globals_0073e8d0()
{
    unknown_profile_ptr_b28cc0 = PlayerProfile::Load_Default();
    unknown_lobbies_b26c88.setEmpty();
    unknown_games_b29990.setEmpty();
    unknown_user_list_count_b2a728 = 0;
    unknown_game_names_b2a648.Clear();
    unknown_known_names_b294b8.Clear();
    unknown_pending_names_b29468.Clear();
    unknown_channel_names_b293a0.Clear();
    unknown_b292dc = time(0) + 86400;
    unknown_b28ff4 = 0;
    unknown_b28ff8 = 0;
    unknown_ladder_b296f8.Clear();
    unknown_ladder_b26970.Clear();
    unknown_channels_b29478.Clear_00766400();
    Clear_Buddy_Lists();
    unknown_names_b29848.Clear_007662f0();
    if (unknown_game_mode_a3d298 == 4 && unknown_a3d2a4 == 2) {
        unknown_b2a7f0 = 0x2300;
        unknown_b26564 = 0x2300;
        unknown_ladder_cache_b2ac24 = &unknown_ladder_b26970;
    } else {
        unknown_b2a7f0 = unknown_protocol_7fd370;
        unknown_b26564 = unknown_protocol_7fd370;
        unknown_ladder_cache_b2ac24 = &unknown_ladder_b2ab98;
    }
    Zero_Record(unknown_channel_b299c0);
    Zero_Record(unknown_pending_channel_b26a60);
    Zero_Record(unknown_game_server_b28cd0);
    Zero_Record(unknown_wdt_server_b29880);
    unknown_connection_error_b2a8ec[0] = 0;
    unknown_b2ac2c = 0;
    unknown_b26898 = 1;
    unknown_b2ab88 = -1;
    unknown_b2a8a4 = time(0);
    unknown_irc_index_b292d8 = 0;
    unknown_irc_index_b2a7f4 = 0;
    unknown_b2ac58 = 0;
    unknown_b2abe0 = 0;
    unknown_b2ac04 = false;
    unknown_b2abd8 = false;
    unknown_7fd2fc = true;
    unknown_motd_b26954.Release();
    memset(wol_wait_events_b264f8, 0, sizeof(wol_wait_events_b264f8));
    unknown_b2abd9 = false;
    unknown_b2abda = false;
    unknown_7fd300 = -1;
    unknown_login_state_00b2abe4 = 0;
    unknown_time_b2abd0 = -1;
    unknown_time_b2abd4 = -1;
    unknown_lobby_names_b26c94[0] = (char *)StringTable::Load_String(wol_lobby_label_1_007fd7d0, 0, wol_source_file_007fd62c, 0x9b5);
    unknown_lobby_names_b26c94[1] = (char *)StringTable::Load_String(wol_lobby_label_2_007fd7c4, 0, wol_source_file_007fd62c, 0x9b6);
    unknown_lobby_names_b26c94[2] = (char *)StringTable::Load_String(wol_lobby_label_3_007fd7b8, 0, wol_source_file_007fd62c, 0x9b7);
    unknown_lobby_names_b26c94[3] = (char *)StringTable::Load_String(wol_lobby_label_4_007fd7ac, 0, wol_source_file_007fd62c, 0x9b8);
    unknown_lobby_names_b26c94[4] = (char *)StringTable::Load_String(wol_lobby_label_5_007fd7a0, 0, wol_source_file_007fd62c, 0x9b9);
    unknown_lobby_names_b26c94[5] = (char *)StringTable::Load_String(wol_lobby_label_6_007fd794, 0, wol_source_file_007fd62c, 0x9ba);
    unknown_lobby_names_b26c94[6] = (char *)StringTable::Load_String(wol_lobby_label_7_007fd788, 0, wol_source_file_007fd62c, 0x9bb);
    unknown_lobby_names_b26c94[7] = (char *)StringTable::Load_String(wol_lobby_label_8_007fd77c, 0, wol_source_file_007fd62c, 0x9bc);
    memset(unknown_b26540, -1, sizeof(unknown_b26540));
    unknown_chat_a72cfc = 0;
    unknown_ladder_client_a72d00 = 0;
    unknown_download_a72d04 = 0;
    wol_chat_cookie_b2ac60 = 0;
    wol_net_cookie_b2ac64 = 0;
    wol_download_cookie_b2ac68 = 0;
    unknown_query_count_b2abf4 = 0;
    unknown_squad_query_b2abf8 = 0;
    memset(unknown_squad_name_b2a8b0, 0, 41);
    unknown_squad_id_b2abfc = 0;
    unknown_b2abe8 = 0;
    ladder_top_rung_b29ce8 = 1;
    wol_lan_leave_b2abf0 = 0;
    unknown_channel_requests_b29390.Set_Empty();
    unknown_b2ac40 = 0;
    unknown_b2ac6c = 0;
    unknown_b2ac70 = 0;
    unknown_b2ac18 = Unknown_006525F0();
    Read_Art_INI();
    unknown_b2ac1c = unknown_art_ini_unique_id();
    unknown_b2ac20 = unknown_ini_8397a0_unique_id();
    unknown_mangler_index_b2ac38 = 0;
}
