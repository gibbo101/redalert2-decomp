// void __fastcall Encode_Game_Options_0073ccb0(char *out) (0x0073CCB0)
// Writes the Westwood Online game options text: the scenario settings, one record per player and
// the computer player tables. The Tiberian Sun twin is Encode_Game_Options. The names of the
// address, port and ping values in the player records are hypotheses.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/ipx_address.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/wide_string.hpp"
#include "shared/wstring.hpp"
#include "shared/session_state.hpp"
extern IPXAddressClass wol_addresses_a3fbd4[8];
extern int wol_ports_a3fc34[],wol_pings_a40238[];
extern char wol_useroptions_b29ad4[512];
// @ref ??_C@_02FAKD@?$EA?3?$AA@=007e6a74
// @ref ??_C@_09IOPK@?$CFd?0?$CFd?0?$CFd?0?$AA@=007e6a68
// @ref ??_C@_0BD@JCLE@?$CFs?0?$CFd?0?$CFd?0?$CFx?0?$CFx?0?$CFx?0?$AA@=007e6a78
// @ref ??_C@_0DE@DGCJ@?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd@=007e6a8c
// @ref ?wol_addresses_a3fbd4@@3PAVIPXAddressClass@@A=00a3fbd4
// @ref ?wol_ports_a3fc34@@3PAHA=00a3fc34
// @ref ?wol_pings_a40238@@3PAHA=00a40238
// @ref ?wol_useroptions_b29ad4@@3PADA=00b29ad4
Wstring __fastcall Wide_To_7_Bit(WideString const &wide);
inline bool Same_Player_Name(unsigned short const *left,unsigned short const *right)
{
    char *name=Unknown_006FA120(left);
    return _stricmp(name,Unknown_006FA120(right))==0;
}
void __fastcall Encode_Game_Options_0073ccb0(char *out)
{
    Wstring name = unknown_map_name_a3d342 ? Wide_To_7_Bit(unknown_map_name_a3d342) : "";
    int value=unknown_session_a3d298.unknown_884;
    sprintf(out,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%s,%s:",unknown_a40d3c,unknown_a40b18,unknown_session_a3d298.GameSpeed_30,unknown_session_a3d298.unknown_24,unknown_session_a3d298.UnitCount,
        unknown_session_a3d298.unknown_2a,unknown_session_a3d298.unknown_2b,unknown_session_a3d298.unknown_2c,unknown_session_a3d298.unknown_a8,unknown_session_a3d298.unknown_crates_29,unknown_session_a3d298.GameModeIndex,
        name.Get(),value,unknown_session_a3d298.ScenarioIsOfficial_880,unknown_session_a3d298.ScenarioFileLength_87c,unknown_session_a3d298.ScenarioFileName_658,unknown_session_a3d298.ScenarioDigest_85a);
    memset(wol_useroptions_b29ad4,0,sizeof(wol_useroptions_b29ad4));
    for(int i=0,count=unknown_players_a3fa7c.Count();i<count;i++) {
        NodeNameType *entry=unknown_players_a3fa7c[i];
        int country=entry->unknown_66e290();
        int color=entry->unknown_66e2a0();
        int address=0,port=0,ping=0;
        for(int j=0;j<8;j++) {
            if(Same_Player_Name(unknown_players_a3fa7c[i]->Name,unknown_session_a3d298.PlayerSlots[j]->Name)) {
                NetNumType net; NetNodeType node; unsigned short socket;
                wol_addresses_a3fbd4[j].Get_Address(net,node,&socket);
                address=*(int *)node;
                port=wol_ports_a3fc34[j];
                ping=wol_pings_a40238[j];
                break;
            }
        }
        Wstring text(Narrow_Copy_00771280(unknown_players_a3fa7c[i]->Name));
        sprintf(wol_useroptions_b29ad4+strlen(wol_useroptions_b29ad4),"%s,%d,%d,%x,%x,%x,",text.Get(),country,color,address,port,ping);
    }
    wol_useroptions_b29ad4[strlen(wol_useroptions_b29ad4)-1]=':';
    strcat(wol_useroptions_b29ad4,"@:");
    for(int k=0;k<8;k++) sprintf(wol_useroptions_b29ad4+strlen(wol_useroptions_b29ad4),"%d,%d,%d,",unknown_session_a3d298.AIDifficulty[k],unknown_session_a3d298.AICountry[k],unknown_session_a3d298.AIColor[k]);
    strcat(out,wol_useroptions_b29ad4);
}
