#include "shared/wol_sink.hpp"
HRESULT __stdcall CChatEventSink::OnChannelList(HRESULT result, WOL::Channel *channels)
{
    Wstring key;
    char query[513];
    memset(query, 0, sizeof(query));
    int queued = 0;
    WolChannelArray old_games;
    if (unknown_b2abd9) return S_OK;
    int request = 0;
    if (result == 0x4013b) request = 0x21;
    else {
        if (unknown_channel_requests_b29390.Get_00768260(request, 0)) unknown_channel_requests_b29390.Remove_007681a0(0);
        if (FAILED(result)) return S_OK;
        if (request == 0) unknown_lobbies_b26c88.Count = 0;
        else {
            Debug_Printf("clearing game list\n");
            WOL::Channel old;
            memset(&old, 0, sizeof(old));
            for (int i = 0; i < unknown_games_b29990.Count; ++i) {
                unknown_games_b29990.Get(old, i);
                if (old.ping != -1) old_games.Insert_00766c20(old, old_games.Count);
            }
            unknown_games_b29990.Count = 0;
        }
    }
    if (channels) {
        do {
            if (channels->unknown_00 == 0) unknown_lobbies_b26c88.Insert_00766c20(*channels, unknown_lobbies_b26c88.Count);
            else if (result == 0x4013b) {
                if (channels->ping != -1) {
                    WOL::Channel *game = 0;
                    for (int i = 0; i < unknown_games_b29990.Count; ++i) {
                        unknown_games_b29990.Get(game, i);
                        if (game && !strcmp(game->name, channels->name)) {
                            Debug_Printf("Setting ping %d for %s\n", channels->ping, channels->name);
                            game->ping = channels->ping;
                            break;
                        }
                    }
                }
            } else {
                unknown_games_b29990.Insert_00766c20(*channels, unknown_games_b29990.Count);
                WOL::Channel old;
                for (int i = 0; i < old_games.Count; ++i) {
                    old_games.Get(old, i);
                    if (!strcmp(old.name, channels->name)) {
                        Debug_Printf("restoring ping %d for channel %s\n", old.ping, channels->name);
                        channels->ping = old.ping;
                        break;
                    }
                }
                key.Set(channels->name);
                key.Truncate_At('\'');
                key.To_Lower();
                if (unknown_game_mode_a3d298 == 4 && unknown_a3d2a4 == 2) {
                    Wstring entry;
                    int name_index = 0;
                    for (; name_index < unknown_game_names_b2a648.Count; ++name_index) {
                        unknown_game_names_b2a648.Get(entry, name_index);
                        if (entry == key) goto game_name_present;
                    }
                    unknown_game_names_b2a648.Prepend(key);
                    game_name_present:;
                }
                if (!unknown_channel_names_b293a0.Contains(key)) {
                    Wstring entry;
                    int name_index = 0;
                    for (; name_index < unknown_pending_names_b29468.Count; ++name_index) {
                        unknown_pending_names_b29468.Get(entry, name_index);
                        if (entry == key) goto pending_name_present;
                    }
                    unknown_pending_names_b29468.Prepend(key);
                    pending_name_present:;
                }
                if (!unknown_ladder_cache_b2ac24->Contains(key)) {
                    strcat(query, key.Get());
                    strcat(query, ":");
                    ++queued;
                }
            }
            if (queued > 20) {
                unknown_ladder_client_a72d00->Request(unknown_ladder_address_b29018, unknown_ladder_port_b2a8ac, query, unknown_protocol_7fd370 & 0xffff00, -1, 0, 0);
                queued = 0;
                memset(query, 0, 512);
            }
            channels = channels->next;
        } while (channels);
        if (queued) {
            unknown_ladder_client_a72d00->Request(unknown_ladder_address_b29018, unknown_ladder_port_b2a8ac, query, unknown_protocol_7fd370 & 0xffff00, -1, 0, 0);
            memset(query, 0, 512);
        }
    }
    SetEvent(unknown_channel_event_b26504);
    if (Is_Online_Session()) Debug_Printf("Received channel list, user list is %d long\n", unknown_user_list_count_b2a728);
    else {
        HWND dialog = (HWND)Unknown_00735940(0x116);
        if (dialog) Unknown_00755180(dialog);
        if (!request) {
            Unknown_0073ee80();
            dialog = (HWND)Unknown_00735940(0x113);
            if (dialog) {
                KillTimer(dialog, 0x55d);
                EnableWindow(GetDlgItem(dialog, 0x55d), true);
            }
        } else Unknown_0073f8f0();
    }
    return S_OK;
}
// @ref ?Insert_00766c20@WolChannelArray@@=00766c20
// @ref ?Get_00768260@WolIntArray@@=00768260
// @ref ?Remove_007681a0@WolIntArray@@=007681a0
// @ref ?Grow_00768320@?$WolArrayList@VWstring@@@@=00768320
// @ref ?unknown_channel_requests_b29390=00b29390
// @ref ?unknown_lobbies_b26c88=00b26c88
// @ref ?unknown_games_b29990=00b29990
// @ref ?unknown_game_names_b2a648=00b2a648
// @ref ?unknown_pending_names_b29468=00b29468
// @ref ?unknown_channel_names_b293a0=00b293a0
// @ref ?unknown_ladder_cache_b2ac24=00b2ac24
// @ref ?unknown_ladder_client_a72d00=00a72d00
// @ref ?unknown_channel_event_b26504=00b26504
// @ref ?unknown_user_list_count_b2a728=00b2a728
// @ref ?Unknown_00755180=00755180
// @ref ?Unknown_0073ee80=0073ee80
// @ref ?Unknown_0073f8f0=0073f8f0
// @ref ?unknown_ladder_address_b29018=00b29018
// @ref ?unknown_ladder_port_b2a8ac=00b2a8ac
// @ref ?unknown_protocol_7fd370=007fd370
// @ref ??_C@_0BE@DACK@clearing?5game?5list?6?$AA@=007fe2b0
// @ref ??_C@_0BI@IGIC@Setting?5ping?5?$CFd?5for?5?$CFs?6?$AA@=007fe298
// @ref ??_C@_0CC@FEKE@restoring?5ping?5?$CFd?5for?5channel?5?$CFs@=007fe274
// @ref ??_C@_01PKAG@?3?$AA@=007e6f8c
// @ref ??_C@_0CN@DEJO@Received?5channel?5list?0?5user?5list@=007fe244
