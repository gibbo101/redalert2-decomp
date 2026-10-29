// 0x00520BF0: tells the player that a lightning storm is already active
// (Msg:LightningStormActive, in the player's colour).
#include "shared/lightning_storm.hpp"
#include "shared/house.hpp"
#include "shared/string_table.hpp"
#include "shared/session_state.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Add_Message@MessageListClass@@QAEPAVUnknownMessageNode@@PBGH0HIH_N@Z=005b4da0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ??_C@_0BJ@IHNF@Msg?3LightningStormActive?$AA@=007ddbe4
// @ref ??_C@_0P@CMOA@D?3?2Ra2?2Ion?4cpp?$AA@=007ddb84

void __fastcall Storm_Active_Message_00520BF0()
{
    wchar_t const *text = StringTable::Load_String("Msg:LightningStormActive", 0, "D:\\Ra2\\Ion.cpp", 1066);
    int color = 3;
    if (unknown_player_a35db4 != 0) {
        color = unknown_player_a35db4->ColorSchemeIndex;
    }
    unknown_session_a3d298.Messages.Add_Message(0, 0, text, color, 0x4046, 150, false);
}
