#include "shared/wol_sink.hpp"
extern char wol_channel_request_debug_7fd6d8[];
// @ref ?wol_channel_request_debug_7fd6d8@@3PADA=007fd6d8
bool __fastcall Request_Channel_List_0073d760(int channel_type,unsigned char autoping)
{
    Debug_Printf(wol_channel_request_debug_7fd6d8,channel_type,autoping);
    if(unknown_chat_a72cfc->unknown_slot06(channel_type,autoping)!=0) return false;
    unknown_channel_requests_b29390.Add_Tail(channel_type);
    return true;
}
