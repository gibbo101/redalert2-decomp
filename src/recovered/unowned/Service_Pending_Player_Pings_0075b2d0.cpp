#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern "C" char *__stdcall inet_ntoa(unsigned long address);
// @ref _inet_ntoa@4=00781b8a
extern char pending_ping_counts_00800008[];
// @ref ?pending_ping_counts_00800008@@3PADA=00800008
extern char pending_ping_request_007ffffc[];
// @ref ?pending_ping_request_007ffffc@@3PADA=007ffffc
extern char pending_ping_started_007fffdc[];
// @ref ?pending_ping_started_007fffdc@@3PADA=007fffdc
extern char pending_ping_no_ip_007fffc8[];
// @ref ?pending_ping_no_ip_007fffc8@@3PADA=007fffc8
extern char pending_ping_missing_007fffb0[];
// @ref ?pending_ping_missing_007fffb0@@3PADA=007fffb0
void __fastcall Service_Pending_Player_Pings_0075b2d0()
{
    bool failed=false;
    WOL::User user;
    memset(&user,0,sizeof(user));
    if(unknown_b2ac40) return;
    Debug_Printf(pending_ping_counts_00800008,unknown_strings_b29980.Count,unknown_strings_b29828.Count);
    while(unknown_strings_b29980.Count && unknown_strings_b29828.Count<10 && !failed) {
        Wstring name;
        unknown_strings_b29980.Get(name,0);
        int index=unknown_users_b2a728.Find_Name(name.Get());
        if(index!=-1) {
            unknown_users_b2a728.Get_Copy(user,index);
            if(user.unknown_18) {
                Debug_Printf(pending_ping_request_007ffffc,name.Get());
                int handle;
                unknown_ladder_client_a72d00->Request_Ping(inet_ntoa(user.unknown_18),1000,&handle);
                if(handle>=0) {
                    unknown_strings_b29828.Insert(name,unknown_strings_b29828.Count);
                    if(unknown_strings_b29980.Count>0) {
                        unknown_strings_b29980.Get(name,0);
                        unknown_strings_b29980.Remove_007661f0(0);
                    }
                    Debug_Printf(pending_ping_started_007fffdc,name.Get());
                } else failed=true;
            } else {
                if(unknown_strings_b29980.Count>0) {
                    unknown_strings_b29980.Get(name,0);
                    unknown_strings_b29980.Remove_007661f0(0);
                }
                Debug_Printf(pending_ping_no_ip_007fffc8,name.Get());
            }
        } else {
            if(unknown_strings_b29980.Count>0) {
                unknown_strings_b29980.Get(name,0);
                unknown_strings_b29980.Remove_Inline(0);
            }
            Debug_Printf(pending_ping_missing_007fffb0,name.Get());
        }
    }
}
