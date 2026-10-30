#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_string.hpp"
extern char wol_broadcast_address_debug_7f1f94[];
extern char wol_session_address_debug_7fecd8[];
// @ref ?wol_broadcast_address_debug_7f1f94@@3PADA=007f1f94
// @ref ?wol_session_address_debug_7fecd8@@3PADA=007fecd8
void __fastcall Users_To_Session_Players_0074d7d0()
{
    unknown_session_a3d55c=1;
    WOL::User user;
    for(int i=0;i<unknown_users_b2a728.Count;++i) {
        unknown_users_b2a728.Get_Copy(user,i);
        NodeNameType *player=Unknown_Find_Lobby_Name_005c8b20(Unknown_006FA180(user.name));
        if(player && Unknown_005c9320(player)) player->unknown_6b=user.unknown_14;
        if(_stricmp(user.name,unknown_wstring_b26cb8.Get())) {
            if(user.flags & 1) {
                NodeNameType *owner=Unknown_Find_Lobby_Name_005c8b20(Unknown_006FA180(user.name));
                NetNumType network;
                NetNodeType node;
                owner->Address.Get_Address(network,node);
                unknown_address_a3db2c.Set_Address(network,node,0);
            }
            int ping=0;
            unknown_ladder_client_a72d00->Get_Average_Ping(user.unknown_18,&ping);
            if(ping<0) ping=0;
            unknown_pings_b2a734[unknown_session_a3d55c++]=ping;
        }
    }
    PacketTransport->unknown_slot12();
    for(i=1;i<unknown_players_a3fa7c.Count();++i) {
        Debug_Printf(wol_broadcast_address_debug_7f1f94,unknown_players_a3fa7c[i]->Address.As_String_00523840());
        PacketTransport->unknown_slot11((char *)&unknown_players_a3fa7c[i]->Address,0);
    }
    Debug_Printf(wol_session_address_debug_7fecd8,unknown_address_a3db2c.As_String_00523840());
}
