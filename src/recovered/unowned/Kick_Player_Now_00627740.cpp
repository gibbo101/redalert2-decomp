// void __fastcall Kick_Player_Now(ConnManClass *net, int index, UnknownFrameTiming *their, unsigned char error) (0x00627740).
#include "shared/queue.hpp"
#include "shared/wol_sink.hpp"
// @ref ?Unknown_005C3150@@YIHPAVHouseClass@@@Z=005c3150
// @ref ?Unknown_0069A160@@YAXXZ=0069a160
// @ref ?Unknown_00698D00@@YIX_N@Z=00698d00
// @ref ?Destroy_Connection_005bb5d0@@YIXHH@Z=005bb5d0
// @ref ??_C@_0CP@HDEF@Kicking?5player?5?$CFd?5from?5the?5game?5@=007ecb9c
// @ref ??_C@_0CI@OHEO@Kick_Player_Now?5bailing?5?9?5bad?5ho@=007ecb74
// @ref ?unknown_flag_a3d8d1@@3_NA=00a3d8d1
// @ref ?unknown_flag_a417c8@@3_NA=00a417c8
// @ref ?unknown_flag_abd500@@3_NA=00abd500
// @ref ?unknown_last_kick_ab6304@@3JA=00ab6304

void __fastcall Kick_Player_Now(ConnManClass *net, int index, UnknownFrameTiming *their, unsigned char error)
{
    bool recent = false;
    int id;
    int i;

    if (time(0) - unknown_last_kick_ab6304 < 60) {
        recent = true;
    }
    unknown_last_kick_ab6304 = time(0);
    id = net->Connection_ID(index);
    Debug_Printf("Kicking player %d from the game - Frame is %d\n", id, ::Frame);
    if (id == -1) {
        Debug_Printf("Kick_Player_Now bailing - bad house ID\n");
        return;
    }
    Houses[id]->unknown_150 = true;
    if (Unknown_005C3150(Houses[id]) == 1 && unknown_game_mode_a3d298 == 4 && !unknown_flag_a417c8) {
        Unknown_0069A160();
        unknown_flag_abd500 = true;
        if (!recent) {
            unknown_flag_a3d8d1 = true;
        }
        for (i = 0; i < Houses.Count(); i++) {
            HouseClass *house = Houses[i];
            if (house && !house->unknown_13d && house->unknown_134) {
                house->unknown_150 = true;
            }
        }
        Unknown_00698D00(false);
    }
    if (Unknown_005C3150(Houses[id]) > 1 && !recent) {
        Houses[id]->unknown_18e = true;
    }
    for (i = index; i < net->Num_Connections() - 1; i++) {
        their[i] = their[i + 1];
        unknown_session_a3d298.KickVotes[i] = unknown_session_a3d298.KickVotes[i + 1];
        unknown_session_a3d298.KickVoters[i] = unknown_session_a3d298.KickVoters[i + 1];
    }
    Destroy_Connection_005bb5d0(id, error);
}
