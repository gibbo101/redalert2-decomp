#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/session_state.hpp"
#include "shared/multi_mission.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/ipx_address.hpp"
#include "shared/crt_stdio.hpp"

bool UnknownSessionState::Log_To_File(_iobuf *out)
{
    int i;
    int j;
    NetNumType net;
    NetNodeType node;

    if (unknown_session_a3d298.ScenarioIndex < 0) {
        fprintf(out, "BOGUS scenario index!?!\n");
        unknown_session_a3d298.ScenarioIndex = 0;
    }

    fprintf(out, "Scenario = %s\n", unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->Description);
    fprintf(out, "Handle = %s\n", Handle);

    for (i = 0; i < NumPlayers; i++) {
        unknown_session_a3d298.Players[i]->Address.Get_Address(net, node);
        fprintf(out, "Player Addr[%d] = ", i);
        for (j = 0; j < sizeof(NetNumType); j++) {
            fprintf(out, "%02X", net[j]);
        }
        fprintf(out, ":");
        for (j = 0; j < sizeof(NetNodeType); j++) {
            fprintf(out, "%02X", node[j]);
        }
        fprintf(out, "\n");
    }
    fprintf(out, "\n");

    unknown_address_a3db2c.Get_Address(net, node);
    fprintf(out, "Address = ");
    for (i = 0; i < sizeof(NetNumType); i++) {
        fprintf(out, "%02X", net[i]);
    }
    fprintf(out, ":");
    for (i = 0; i < sizeof(NetNodeType); i++) {
        fprintf(out, "%02X", node[i]);
    }
    fprintf(out, "\n\n");
    fprintf(out, "MaxAhead = %d\n", MaxAhead_2c8);
    fprintf(out, "LoadGame = %d\n", LoadGame);
    fprintf(out, "PrefColor = %d\n", unknown_12c);
    fprintf(out, "ColorIdx = %d\n", unknown_11c);
    fprintf(out, "House = %d\n", unknown_124);
    fprintf(out, "NumPlayers = %d\n", NumPlayers);
    fprintf(out, "Options.Bases = %d\n", unknown_bases_20);
    fprintf(out, "Options.Credits = %d\n", unknown_24);
    fprintf(out, "Options.BridgeDestruction = %d\n", unknown_28);
    fprintf(out, "Options.Goodies = %d\n", unknown_crates_29);
    fprintf(out, "Options.Ghosts = %d\n", unknown_ghosts_35);
    fprintf(out, "Options.UnitCount = %d\n", UnitCount);
    fprintf(out, "Options.AIPlayers = %d\n", AICount);
    fprintf(out, "Options.AIDifficulty = %d\n", unknown_difficulty_40);
    fprintf(out, "ObiWan = %d\n", unknown_2b0);

    if (unknown_session_a3d298.Type == 3) {
        fprintf(out, "Type = IPX\n");
    } else if (unknown_session_a3d298.Type == 4) {
        fprintf(out, "Type = INTERNET\n");
    } else {
        fprintf(out, "Type = !!Unknown!!\n");
    }
    return true;
}
// @ref ??_C@_0BJ@JMAJ@BOGUS?5scenario?5index?$CB?$DP?$CB?6?$AA@=007f3870
// @ref ??_C@_0P@MPBH@Scenario?5?$DN?5?$CFs?6?$AA@=007f3860
// @ref ??_C@_0N@ELDB@Handle?5?$DN?5?$CFs?6?$AA@=007f3850
// @ref ??_C@_0BD@DLGH@Player?5Addr?$FL?$CFd?$FN?5?$DN?5?$AA@=007f383c
// @ref ??_C@_04LDEB@?$CF02X?$AA@=007f3834
// @ref ??_C@_0L@CCHN@Address?5?$DN?5?$AA@=007f3824
// @ref ??_C@_02JJJH@?6?6?$AA@=007f3820
// @ref ??_C@_0P@IHBC@MaxAhead?5?$DN?5?$CFd?6?$AA@=007f3810
// @ref ??_C@_0P@OJHB@LoadGame?5?$DN?5?$CFd?6?$AA@=007f3800
// @ref ??_C@_0BA@KENM@PrefColor?5?$DN?5?$CFd?6?$AA@=007f37f0
// @ref ??_C@_0P@LLDK@ColorIdx?5?$DN?5?$CFd?6?$AA@=007f37e0
// @ref ??_C@_0M@OIGP@House?5?$DN?5?$CFd?6?$AA@=007f37d4
// @ref ??_C@_0BB@HCAN@NumPlayers?5?$DN?5?$CFd?6?$AA@=007f37c0
// @ref ??_C@_0BE@LIDH@Options?4Bases?5?$DN?5?$CFd?6?$AA@=007f37ac
// @ref ??_C@_0BG@CAKD@Options?4Credits?5?$DN?5?$CFd?6?$AA@=007f3794
// @ref ??_C@_0CA@MMGL@Options?4BridgeDestruction?5?$DN?5?$CFd?6?$AA@=007f3774
// @ref ??_C@_0BG@EFAO@Options?4Goodies?5?$DN?5?$CFd?6?$AA@=007f375c
// @ref ??_C@_0BF@FJMB@Options?4Ghosts?5?$DN?5?$CFd?6?$AA@=007f3744
// @ref ??_C@_0BI@JKCA@Options?4UnitCount?5?$DN?5?$CFd?6?$AA@=007f372c
// @ref ??_C@_0BI@NHKB@Options?4AIPlayers?5?$DN?5?$CFd?6?$AA@=007f3714
// @ref ??_C@_0BL@HGJC@Options?4AIDifficulty?5?$DN?5?$CFd?6?$AA@=007f36f8
// @ref ??_C@_0N@NECL@ObiWan?5?$DN?5?$CFd?6?$AA@=007f36e8
// @ref ??_C@_0M@OAAD@Type?5?$DN?5IPX?6?$AA@=007f36dc
// @ref ??_C@_0BB@DAID@Type?5?$DN?5INTERNET?6?$AA@=007f36c8
// @ref ??_C@_0BE@IE@Type?5?$DN?5?$CB?$CBUnknown?$CB?$CB?6?$AA@=007f36b4
// @ref ??_C@_01BJG@?6?$AA@=007f3830
// @ref ??_C@_01PKAG@?3?$AA@=007e6f8c
