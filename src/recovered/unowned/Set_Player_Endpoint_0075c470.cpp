#include "shared/wol_sink.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/ipx_address.hpp"
#include "shared/crt_string.hpp"
extern "C" int __cdecl sscanf(char const *,char const *,...);
extern char endpoint_number_format_007db4b0[];
extern IPXAddressClass unknown_addresses_a3fbd4[8];
extern int unknown_peer_values_a3fc34[8];
extern int unknown_peer_values_a40238[8];
// @ref ?endpoint_number_format_007db4b0@@3PADA=007db4b0
// @ref ?unknown_addresses_a3fbd4@@3PAVIPXAddressClass@@A=00a3fbd4
// @ref ?unknown_peer_values_a3fc34@@3PAHA=00a3fc34
// @ref ?unknown_peer_values_a40238@@3PAHA=00a40238
// @ref _sscanf=00783730
void __fastcall Set_Player_Endpoint_0075c470(char const *name,char const *address_text,char const *value_text,char const *other_text)
{
    if(name && address_text && value_text && other_text) {
        unsigned int address=0;
        unsigned int value=0;
        unsigned int other=0;
        sscanf(address_text,endpoint_number_format_007db4b0,&address);
        sscanf(value_text,endpoint_number_format_007db4b0,&value);
        sscanf(other_text,endpoint_number_format_007db4b0,&other);
        int i=0;
        for(NodeNameType **slot=unknown_player_slots_a3fa98;(long)slot<(long)(unknown_player_slots_a3fa98+8);++slot,++i) {
            if(_stricmp(name,Unknown_006FA120((*slot)->Name))==0) {
                NetNodeType node;
                NetNumType net;
                memset(node,0,sizeof(node));
                memset(net,0,sizeof(net));
                memcpy(node,&address,4);
                unknown_addresses_a3fbd4[i].Set_Address(net,node,0);
                unknown_peer_values_a3fc34[i]=value;
                unknown_peer_values_a40238[i]=other;
                break;
            }
        }
    }
}
