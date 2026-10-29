// HRESULT __stdcall CChatEventSink::OnGameStart(HRESULT result, WOL::Channel *channel, WOL::User *users, int game_id) (0x00761570, slot 23)
// Starts the game once every listed player is in the user list: records the game id, protocol,
// host and start time, then sets up the session's players.
#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_timer_b292e8@@3V?$CDTimerClass@VSystemTimerClass@@@@A=00b292e8
// @ref ?unknown_b2ac45@@3_NA=00b2ac45
// @ref ?unknown_b2ac44@@3_NA=00b2ac44
// @ref ?unknown_b2ac04@@3_NA=00b2ac04
// @ref ?unknown_b2ac40@@3HA=00b2ac40
// @ref ?unknown_login_state_00b2abe4@@3HA=00b2abe4
// @ref ?unknown_protocol_7fd370@@3IA=007fd370
// @ref ?unknown_b2668c@@3HA=00b2668c
// @ref ?unknown_b299d4@@3HA=00b299d4
// @ref ?unknown_wstring_b26cb8@@3VWstring@@A=00b26cb8
// @ref ?unknown_b2a808@@3PADA=00b2a808
// @ref ?unknown_game_start_time_b2a638@@3JA=00b2a638
// @ref ?unknown_session_a3fc54@@3PADA=00a3fc54
// @ref ?unknown_session_a40054@@3HA=00a40054
// @ref ?unknown_b2abec@@3HA=00b2abec
// @ref ?Unknown_0074d7d0@@YIXPAUUser@WOL@@@Z=0074d7d0
// @ref ?Unknown_0074e070@@YIHPAX@Z=0074e070
// @ref ?unknown_a3d2a4@@3HA=00a3d2a4
// @ref ?unknown_b2a7fc@@3HA=00b2a7fc
// @ref ?unknown_b2ab84@@3IA=00b2ab84
// @ref ?unknown_b2a7ec@@3HA=00b2a7ec
// @ref ?unknown_b2a6d8@@3PADA=00b2a6d8
// @ref ?Unknown_006FA0C0@@YIXPAGPBDH@Z=006fa0c0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref _time=0078387f

HRESULT __stdcall CChatEventSink::OnGameStart(HRESULT result, WOL::Channel *channel, WOL::User *users, int game_id)
{
    bool all_found = true;
    int count = unknown_users_b2a728.Count;
    int listed = 0;
    unknown_timer_b292e8 = CDTimerClass<SystemTimerClass>(0);
    if (unknown_b2ac45) return S_OK;
    unknown_login_state_00b2abe4 = 1;
    WOL::User *user = users;
    while (user) {
        ++listed;
        Wstring name(user->name);
        name.To_Lower();
        int i;
        for (i = 0; i < count; ++i) {
            WOL::User entry;
            unknown_users_b2a728.Get_Copy(entry, i);
            Wstring other(entry.name);
            other.To_Lower();
            if (name == other) break;
        }
        if (i >= count) {
            all_found = false;
            break;
        }
        user = user->next;
    }
    bool ok = listed == count && all_found;
    if (!ok) {
        unknown_b2ac04 = false;
        unknown_b2ac40 = 0;
    } else {
        if (unknown_a3d2a4 == 2 || unknown_a3d2a4 == 1) {
            void *dialog = Unknown_00735940(0x117);
            Unknown_007357E0(dialog, 0);
        }
        unknown_b2a7fc = game_id;
        unknown_b2ab84 = unknown_protocol_7fd370;
        unknown_b2668c = 0x2300;
        unknown_b2a7ec = unknown_b299d4;
        if (Unknown_0073c3a0()) unknown_b2a7ec = 2;
        strcpy(unknown_b2a6d8, unknown_wstring_b26cb8.Get());
        WOL::User *first = 0;
        unknown_users_b2a728.Get(first, 0);
        if (first) strcpy(unknown_b2a808, first->name);
        unknown_game_start_time_b2a638 = time(0);
        Debug_Printf("OnGameStart\n");
        if (channel) unknown_b2abec = channel->unknown_20 & 0xff;
        unknown_b2ac44 = false;
        unknown_b2ac45 = true;
        Unknown_0074d7d0(users);
        unknown_b2ac40 = 2;
        Debug_Printf("Starting a %d player game.\n", unknown_session_a3d55c);
        WOL::User *host = Unknown_0074DA60();
        if (host) Unknown_006FA0C0(unknown_session_a3d298.MasterPlayerName, host->name, -1);
        unknown_session_a3d298.MasterPlayerID = -1;
        unknown_session_a40054 = Unknown_0074e070(unknown_session_a3fc54);
    }
    return S_OK;
}
// @ref ??_C@_0BM@JHOP@Starting?5a?5?$CFd?5player?5game?4?6?$AA@=007fded4
// @ref ??_C@_0N@JLDN@OnGameStart?6?$AA@=007fdef0
