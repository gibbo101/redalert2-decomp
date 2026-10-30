#include "shared/wol_sink.hpp"
extern HANDLE wol_wait_events_b264f8[18];
bool __fastcall Get_Channel_List_0073d8f0();
bool __fastcall Request_Channel_List_0073d760(int channel_type,unsigned char autoping);
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
bool __fastcall Queue_Channel_List_Request_0073db20(int channel_type,unsigned char autoping,bool wait)
{
    if(unknown_channel_requests_b29390.Count) {
        bool result=Get_Channel_List_0073d8f0();
        if(!result) return result;
    }
    for(int i=0;i<18;++i) ResetEvent(wol_wait_events_b264f8[i]);
    if(!Request_Channel_List_0073d760(channel_type,autoping)) {
        SetEvent(wol_wait_events_b264f8[0]);
        return false;
    }
    if(wait) return Get_Channel_List_0073d8f0();
    return true;
}
