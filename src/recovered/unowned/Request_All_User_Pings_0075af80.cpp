#include "shared/wol_sink.hpp"
#include "shared/debug_printf.hpp"
extern "C" char *__stdcall inet_ntoa(unsigned long address);
extern char ping_request_debug_007fdde0[];
// @ref _inet_ntoa@4=00781b8a
// @ref ?ping_request_debug_007fdde0@@3PADA=007fdde0
void Request_All_User_Pings_0075af80()
{
    if(unknown_b2ac40==0) {
        WOL::User user;
        memset(&user,0,sizeof(user));
        int handle=0;
        int count=unknown_users_b2a728.Count;
        for(int i=0;i<count;++i) {
            unknown_users_b2a728.Get_Copy(user,i);
            unsigned long address=user.unknown_18;
            Debug_Printf(ping_request_debug_007fdde0,user.name,inet_ntoa(address));
            unknown_ladder_client_a72d00->Request_Ping(inet_ntoa(address),1000,&handle);
        }
    }
}
