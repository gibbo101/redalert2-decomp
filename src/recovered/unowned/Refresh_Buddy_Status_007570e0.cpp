#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
extern "C" long __cdecl time(long *);
extern HANDLE wol_wait_events_b264f8[18];
extern unsigned long buddy_refresh_time_b2a6f0;
bool __fastcall Queue_Channel_List_Request_0073db20(int channel_type,unsigned char autoping,bool wait);
void Service_Buddy_Find_Queue_00756610();
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?buddy_refresh_time_b2a6f0@@3KA=00b2a6f0
inline bool Request_Buddy_Channel_List()
{
    return Queue_Channel_List_Request_0073db20(0x21, 1, false);
}

void Refresh_Buddy_Status_007570e0()
{
    buddy_refresh_time_b2a6f0 = time(0);
    if (!Request_Buddy_Channel_List()) {
        SetEvent(wol_wait_events_b264f8[5]);
        return;
    }
    unknown_strings_b29838.Clear();
    for (int i = 0; i < unknown_strings_b26920.Count; i++) {
        Wstring name;
        unknown_strings_b26920.Get(name, i);
        unknown_strings_b29838.Add_Tail(name);
    }
    Service_Buddy_Find_Queue_00756610();
}
