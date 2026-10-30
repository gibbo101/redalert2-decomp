// void __fastcall Unknown_005c3810(bool unknown_1, bool unknown_2) (0x005C3810)
// Sends the game options when the session's settings differ from the last sent copy (or a resend is
// forced), at most once a second; the copy is refreshed before the send.
#include "shared/lobby.hpp"
#include "shared/crt_time.hpp"
#include "shared/crt_string.hpp"
#include "shared/session_state.hpp"
#include "shared/ipx_manager.hpp"
// @ref ?unknown_sent_time_a72d48@@3JA=00a72d48
// @ref ?unknown_send_pending_a72d4c@@3_NA=00a72d4c
// @ref ?unknown_sent_speed_7e6dc4@@3HA=007e6dc4
// @ref ?unknown_sent_24_7e6dc8@@3HA=007e6dc8
// @ref ?unknown_sent_units_7e6dcc@@3HA=007e6dcc
// @ref ?unknown_sent_official_7e6dd0@@3_NA=007e6dd0
// @ref ?unknown_sent_length_7e6dd4@@3HA=007e6dd4
// @ref ?unknown_sent_2a_a72d4d@@3_NA=00a72d4d
// @ref ?unknown_sent_2b_a72d4e@@3_NA=00a72d4e
// @ref ?unknown_sent_2c_a72d4f@@3_NA=00a72d4f
// @ref ?unknown_sent_a8_a72d50@@3_NA=00a72d50
// @ref ?unknown_sent_crates_a72d51@@3_NA=00a72d51
// @ref ?unknown_sent_map_name_a72c90@@3PAGA=00a72c90
// @ref ?unknown_sent_file_name_a72890@@3PADA=00a72890
// @ref ?unknown_sent_digest_a728a0@@3PADA=00a728a0
// @ref ?Build_Game_Options_005bc940@@YIXPAD@Z=005bc940
// @ref ?Unknown_0073ccb0@@YIXPAD@Z=0073ccb0

extern long unknown_sent_time_a72d48;
extern bool unknown_send_pending_a72d4c;
extern int unknown_sent_speed_7e6dc4;
extern int unknown_sent_24_7e6dc8;
extern int unknown_sent_units_7e6dcc;
extern bool unknown_sent_official_7e6dd0;
extern int unknown_sent_length_7e6dd4;
extern bool unknown_sent_2a_a72d4d;
extern bool unknown_sent_2b_a72d4e;
extern bool unknown_sent_2c_a72d4f;
extern bool unknown_sent_a8_a72d50;
extern bool unknown_sent_crates_a72d51;
extern unsigned short unknown_sent_map_name_a72c90[44];
extern char unknown_sent_file_name_a72890[14];
extern char unknown_sent_digest_a728a0[33];

void __fastcall Unknown_005c3810(bool unknown_1, bool unknown_2)
{
    char buffer[0x208];
    bool changed = false;
    if (time(0) - unknown_sent_time_a72d48 == 0) {
        if (unknown_1) {
            unknown_send_pending_a72d4c = true;
        }
        if (!unknown_2) {
            return;
        }
    }
    if (unknown_send_pending_a72d4c) {
        unknown_1 = true;
    }
    unknown_send_pending_a72d4c = false;
    if (unknown_chat_a72cfc != 0) {
        if (time(0) - unknown_sent_time_a72d48 >= 5) {
            changed = true;
        }
    } else {
        if (time(0) - unknown_sent_time_a72d48 >= 2) {
            changed = true;
        }
    }
    if (unknown_1) {
        changed = true;
    }
    if (unknown_sent_speed_7e6dc4 != unknown_session_a3d298.GameSpeed_30) {
        changed = true;
    }
    if (unknown_sent_24_7e6dc8 != unknown_session_a3d298.unknown_24) {
        changed = true;
    }
    if (unknown_sent_units_7e6dcc != unknown_session_a3d298.UnitCount) {
        changed = true;
    }
    if (unknown_sent_2a_a72d4d != unknown_session_a3d298.unknown_2a) {
        changed = true;
    }
    if (unknown_sent_2b_a72d4e != unknown_session_a3d298.unknown_2b) {
        changed = true;
    }
    if (unknown_sent_2c_a72d4f != unknown_session_a3d298.unknown_2c) {
        changed = true;
    }
    if (unknown_sent_a8_a72d50 != unknown_session_a3d298.unknown_a8) {
        changed = true;
    }
    if (unknown_sent_crates_a72d51 != unknown_session_a3d298.unknown_crates_29) {
        changed = true;
    }
    unknown_sent_map_name_a72c90[43] = 0;
    if (_wcsicmp(unknown_sent_map_name_a72c90, unknown_map_name_a3d342) != 0) {
        changed = true;
    }
    unknown_sent_file_name_a72890[13] = 0;
    if (_stricmp(unknown_sent_file_name_a72890, unknown_session_a3d298.ScenarioFileName_658) != 0) {
        changed = true;
    }
    unknown_sent_digest_a728a0[32] = 0;
    if (_stricmp(unknown_sent_digest_a728a0, unknown_session_a3d298.ScenarioDigest_85a) != 0) {
        changed = true;
    }
    if (unknown_sent_length_7e6dd4 != unknown_session_a3d298.ScenarioFileLength_87c) {
        changed = true;
    }
    if (unknown_sent_official_7e6dd0 != unknown_session_a3d298.ScenarioIsOfficial_880) {
        changed = true;
    }
    if (!changed) {
        return;
    }
    unknown_sent_time_a72d48 = time(0);
    unknown_sent_speed_7e6dc4 = unknown_session_a3d298.GameSpeed_30;
    unknown_sent_24_7e6dc8 = unknown_session_a3d298.unknown_24;
    unknown_sent_units_7e6dcc = unknown_session_a3d298.UnitCount;
    unknown_sent_2a_a72d4d = unknown_session_a3d298.unknown_2a;
    unknown_sent_2b_a72d4e = unknown_session_a3d298.unknown_2b;
    unknown_sent_2c_a72d4f = unknown_session_a3d298.unknown_2c;
    unknown_sent_a8_a72d50 = unknown_session_a3d298.unknown_a8;
    unknown_sent_crates_a72d51 = unknown_session_a3d298.unknown_crates_29;
    wcscpy(unknown_sent_map_name_a72c90, unknown_map_name_a3d342);
    strcpy(unknown_sent_digest_a728a0, unknown_session_a3d298.ScenarioDigest_85a);
    strcpy(unknown_sent_file_name_a72890, unknown_session_a3d298.ScenarioFileName_658);
    unknown_sent_length_7e6dd4 = unknown_session_a3d298.ScenarioFileLength_87c;
    unknown_sent_official_7e6dd0 = unknown_session_a3d298.ScenarioIsOfficial_880;
    memset(buffer, 0, sizeof(buffer));
    if (unknown_chat_a72cfc != 0) {
        Unknown_0073ccb0(buffer);
        Send_Game_Options_005c3c60(buffer);
    } else {
        Build_Game_Options_005bc940(buffer);
        Send_Game_Options_005c3c60(buffer);
    }
}
