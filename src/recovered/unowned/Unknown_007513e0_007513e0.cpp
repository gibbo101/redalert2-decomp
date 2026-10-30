// @ref ??_C@_09PKEM@Ol?5Cruddy?$AA@=007ff940
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/wol_sink.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/crt_memory.hpp"
#pragma auto_inline(off)
void __fastcall Unknown_007513e0()
{
    NodeNameType *player=new NodeNameType;
    Unknown_006FA0C0(player->Name,"Ol Cruddy",-1);
    player->unknown_6b=-1;
    player->unknown_4b=0;
    player->unknown_53=3;
    NetNumType network;
    NetNodeType node;
    memset(network,0,sizeof(network));
    node[5]=0;
    node[4]=0;
    node[3]=82;
    node[2]=81;
    node[1]=2;
    node[0]=10;
    player->Address.Set_Address(network,node,0);
    unknown_players_a3fa7c.Add(player);
    unknown_pings_b2a734[unknown_session_a3d55c]=100;
    ++unknown_session_a3d55c;
}

#pragma auto_inline(on)
