// @ref ??_C@_09HMPI@PotatoToo?$AA@=007ff954
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/wol_sink.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/crt_memory.hpp"
void __fastcall Unknown_007515b0()
{
    NodeNameType *player=new NodeNameType;
    Unknown_006FA0C0(player->Name,"PotatoToo",-1);
    player->unknown_6b=-1;
    player->unknown_4b=1;
    player->unknown_53=2;
    NetNumType network;
    NetNodeType node;
    memset(network,0,sizeof(network));
    node[5]=0;
    node[4]=0;
    node[3]=250;
    node[2]=80;
    node[1]=2;
    node[0]=10;
    player->Address.Set_Address(network,node,0);
    unknown_players_a3fa7c.Add(player);
    unknown_pings_b2a734[unknown_session_a3d55c]=100;
    ++unknown_session_a3d55c;
    unknown_address_a3db2c=player->Address;
}
