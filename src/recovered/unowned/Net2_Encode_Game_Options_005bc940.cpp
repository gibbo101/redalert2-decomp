// @ref ??_C@_00A@?$AA@=0083c55c
// Encodes the LAN scenario settings, players, and computer-player options.
#include "shared/debug_printf.hpp"
extern char const net2_debug_length_7e6a44[],net2_debug_options_7e6a34[];
// @ref ?net2_debug_length_7e6a44@@3QBDB=007e6a44
// @ref ?net2_debug_options_7e6a34@@3QBDB=007e6a34
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/ipx_address.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/wide_string.hpp"
#include "shared/wstring.hpp"
#include "shared/session_state.hpp"
extern char net2_useroptions_a71bdc[512];
// @ref ??_C@_02FAKD@?$EA?3?$AA@=007e6a74
// @ref ??_C@_09IOPK@?$CFd?0?$CFd?0?$CFd?0?$AA@=007e6a68
// @ref ??_C@_0BD@JCLE@?$CFs?0?$CFd?0?$CFd?0?$CFx?0?$CFx?0?$CFx?0?$AA@=007e6a78
// @ref ??_C@_0DE@DGCJ@?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd@=007e6a8c
// @ref ?net2_useroptions_a71bdc@@3PADA=00a71bdc
Wstring __fastcall Wide_To_7_Bit(WideString const &wide);

void __fastcall Build_Game_Options_005bc940(char *out)
{
    Wstring name = unknown_map_name_a3d342 ? Wide_To_7_Bit(unknown_map_name_a3d342) : "";
    int value=unknown_session_a3d298.unknown_884;
    sprintf(out,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%s,%s:",unknown_a40d3c,unknown_a40b18,unknown_session_a3d298.GameSpeed_30,unknown_session_a3d298.unknown_24,unknown_session_a3d298.UnitCount,
        unknown_session_a3d298.unknown_2a,unknown_session_a3d298.unknown_2b,unknown_session_a3d298.unknown_2c,unknown_session_a3d298.unknown_a8,unknown_session_a3d298.unknown_crates_29,unknown_session_a3d298.GameModeIndex,
        name.Get(),value,unknown_session_a3d298.ScenarioIsOfficial_880,unknown_session_a3d298.ScenarioFileLength_87c,unknown_session_a3d298.ScenarioFileName_658,unknown_session_a3d298.ScenarioDigest_85a);
    memset(net2_useroptions_a71bdc,0,sizeof(net2_useroptions_a71bdc));
    for(int i=0,count=unknown_players_a3fa7c.Count();i<count;i++) {
        NodeNameType *entry=unknown_players_a3fa7c[i];
        int country=entry->unknown_66e290();
        int color=entry->unknown_66e2a0();
        unsigned short const *player_name=unknown_players_a3fa7c[i]->Name;
        sprintf(net2_useroptions_a71bdc+strlen(net2_useroptions_a71bdc),"%s,%d,%d,%x,%x,%x,",Unknown_006FA120(player_name),country,color,0,0,0);
    }
    net2_useroptions_a71bdc[strlen(net2_useroptions_a71bdc)-1]=':';
    strcat(net2_useroptions_a71bdc,"@:");
    for(int k=0;k<8;k++) {
        sprintf(net2_useroptions_a71bdc+strlen(net2_useroptions_a71bdc),"%d,%d,%d,",unknown_session_a3d298.AIDifficulty[k],unknown_session_a3d298.AICountry[k]==-3 ? -1 : unknown_session_a3d298.AICountry[k],unknown_session_a3d298.AIColor[k]);
    }
    Debug_Printf(net2_debug_length_7e6a44,strlen(net2_useroptions_a71bdc));
    Debug_Printf(net2_debug_options_7e6a34,net2_useroptions_a71bdc);
    strcat(out,net2_useroptions_a71bdc);
}
