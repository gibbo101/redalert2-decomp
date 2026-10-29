// void __fastcall Unknown_00627210(int id, int index) (0x00627210): a kick vote, shown in the reconnect dialog.
#include "shared/queue.hpp"
#include "shared/wol_sink.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
// @ref ?Unknown_005C2DA0@@YIXHPBGPAUHWND__@@@Z=005c2da0
// @ref ?Unknown_00735B10@@YAPAUHWND__@@XZ=00735b10
// @ref ??_C@_0DB@HONA@Player?5?$CFs?5votes?5to?5kick?5player?5?$CF@=007ecb40
// @ref ??_C@_0BM@LLBA@TXT_RECONNECT_KICK_RECEIVED?$AA@=007ecb24
// @ref ??_C@_0BB@FEBL@D?3?2Ra2?2Queue?4CPP?$AA@=007ec598

void __fastcall Unknown_00627210(int id, int index)
{
    int i;
    wchar_t buffer[256];
    wchar_t *name;

    for (i = 0; i < unknown_session_a3d298.KickVotes[index]; i++) {
        if (unknown_session_a3d298.KickVoters[index].ID[i] == id) {
            return;
        }
    }
    unknown_session_a3d298.KickVoters[index].ID[unknown_session_a3d298.KickVotes[index]] = id;
    unknown_session_a3d298.KickVotes[index]++;
    if (unknown_session_a3d298.Type == 3 || unknown_session_a3d298.Type == 4) {
        name = unknown_ipx_manager_a40978.Connection_Name(id);
        if (!name) {
            name = unknown_session_a3d298.Players[0]->Name;
        }
        Debug_Printf("Player %s votes to kick player %s from the game\n", name, unknown_ipx_manager_a40978.Connection_Name(index));
        swprintf(buffer, StringTable::Load_String("TXT_RECONNECT_KICK_RECEIVED", 0, "D:\\Ra2\\Queue.CPP", 3488), name, unknown_ipx_manager_a40978.Connection_Name(index));
        HWND dialog = Unknown_00735B10();
        HWND list = GetDlgItem(dialog, 0x651);
        Unknown_005C2DA0(-1, buffer, list);
        Unknown_00626FA0(list);
    }
}
