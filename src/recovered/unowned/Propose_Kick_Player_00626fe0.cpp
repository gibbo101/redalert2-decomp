// void __fastcall Propose_Kick_Player(HWND dialog, int index) (0x00626FE0; named by its trace).
#include "shared/queue.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
// @ref ?Unknown_005C2DA0@@YIXHPBGPAUHWND__@@@Z=005c2da0
// @ref ??_C@_0BI@DEM@TXT_RECONNECT_KICK_SELF?$AA@=007ecadc
// @ref ??_C@_0O@NJFP@TXT_CANT_KICK?$AA@=007ecacc
// @ref ??_C@_0BN@FDKG@Sending?5kick?5proposal?5to?5?$CFs?6?$AA@=007ecaac
// @ref ??_C@_0CN@PLCN@Propose_Kick_Player?5?$CFd?5?9?5?$CFs?4?5Loc@=007ecaf4
// @ref ??_C@_0BB@FEBL@D?3?2Ra2?2Queue?4CPP?$AA@=007ec598

void __fastcall Propose_Kick_Player(HWND dialog, int index)
{
    if (index < 0 || index >= unknown_session_a3d298.Players.Count()) {
        return;
    }
    Debug_Printf("Propose_Kick_Player %d - %s. Local id is %d\n", index, unknown_session_a3d298.Players[index]->Name,
        unknown_session_a3d298.Players[0]->ID);
    HWND list = GetDlgItem(dialog, 0x651);
    if (index == 0) {
        Unknown_005C2DA0(-1, StringTable::Load_String("TXT_RECONNECT_KICK_SELF", 0, "D:\\Ra2\\Queue.CPP", 3378), list);
        Unknown_00626FA0(list);
        return;
    }
    if (unknown_session_a3d298.Type == 4 && unknown_b2a7ec) {
        Unknown_005C2DA0(-1, StringTable::Load_String("TXT_CANT_KICK", 0, "D:\\Ra2\\Queue.CPP", 3388), list);
        Unknown_00626FA0(list);
        return;
    }

    UnknownGlobalPacket packet;
    packet.Command = 0x1C;
    strncpy(packet.Name, Unknown_006FA120(unknown_session_a3d298.Players[0]->Name), 20);
    packet.Kick.Proposer = unknown_session_a3d298.Players[0]->ID;
    packet.Kick.Kickee = unknown_session_a3d298.Players[index]->ID;
    for (int i = 1; i < unknown_session_a3d298.Players.Count(); i++) {
        Debug_Printf("Sending kick proposal to %s\n", unknown_session_a3d298.Players[i]->Name);
        unknown_ipx_manager_a40978.Send_Global_Message(&packet, 0x1C7, 1, &unknown_session_a3d298.Players[i]->Address, 0, 0);
    }
    Unknown_00627210(unknown_session_a3d298.Players[0]->ID, unknown_session_a3d298.Players[index]->ID);
}
