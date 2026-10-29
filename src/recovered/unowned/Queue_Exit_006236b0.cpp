// bool __fastcall Queue_Exit() (0x006236B0): EXIT, or 0x27 when the master leaves a network game of more than two players.
#include "shared/queue.hpp"
#include "shared/session_state.hpp"
// @ref ??0EventClass@@QAE@HE@Z=004b5fd0
// @ref ?Am_I_Master@UnknownSessionState@@QAE_NPAVHouseClass@@@Z=0066f150

bool __fastcall Queue_Exit()
{
    unsigned char type = 0x13;
    if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8 && unknown_session_a3d298.Players.Count() > 2 && unknown_session_a3d298.Am_I_Master(0)) {
        type = 0x27;
    }
    if (!OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, type))) {
        return false;
    }
    return true;
}
