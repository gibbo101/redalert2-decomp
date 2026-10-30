#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern char private_port_format_007ce9bc[];
extern char private_port_debug_007fef8c[];
// @ref ?private_port_format_007ce9bc@@3PADA=007ce9bc
// @ref ?private_port_debug_007fef8c@@3PADA=007fef8c
void __fastcall Send_User_Port_0074e330(char const *name,unsigned short port)
{
    WOL::User *user=0;
    char text[256];
    for(int i=0;i<unknown_users_b2a728.Count;++i) {
        unknown_users_b2a728.Get(user,i);
        if(_stricmp(name,user->name)==0) {
            text[0]='Z';
            text[1]='4';
            sprintf(text+2,private_port_format_007ce9bc,port);
            Debug_Printf(private_port_debug_007fef8c,text,name);
            unknown_chat_a72cfc->unknown_slot14(user,text);
        }
    }
}
