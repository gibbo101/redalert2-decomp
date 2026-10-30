#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
extern char wol_user_pings_debug_007fff88[];
extern char wol_user_ping_format_007fffa8[];
void __fastcall Store_User_Ping_0075b110(char const *name,int ping);
// @ref ?wol_user_pings_debug_007fff88@@3PADA=007fff88
// @ref ?wol_user_ping_format_007fffa8@@3PADA=007fffa8
// @ref ?Store_User_Ping_0075b110@@YIXPBDH@Z=0075b110
void __fastcall Unknown_0075b1b0()
{
    int count=unknown_users_b2a728.Count;
    WOL::User user;
    memset(&user,0,sizeof(user));
    char message[256];
    char entry[128];
    int ping;
    message[0]='P';
    message[1]=(char)count+'0';
    message[2]=0;
    if(!unknown_b2ac40) {
        for(int i=0;i<count;++i) {
            unknown_users_b2a728.Get_Copy(user,i);
            unknown_ladder_client_a72d00->Get_Average_Ping(user.unknown_18,&ping);
            sprintf(entry,wol_user_ping_format_007fffa8,user.name,ping);
            strcat(message,entry);
            Store_User_Ping_0075b110(user.name,ping);
        }
        Debug_Printf(wol_user_pings_debug_007fff88,message);
        Send_Game_Options_005c3c60(message);
    }
}
