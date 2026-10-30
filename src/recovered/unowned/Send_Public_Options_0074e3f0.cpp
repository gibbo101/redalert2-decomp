#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern char public_options_message_7e71f0[];
// @ref ?public_options_message_7e71f0@@3PADA=007e71f0
void __fastcall Send_Public_Options_0074e3f0(char kind,char const *text)
{
    char options[256];
    options[0]='Z';
    options[1]='1';
    options[2]=kind+'0';
    if(text) strcpy(options+3,text);
    else options[3]=0;
    Debug_Printf(public_options_message_7e71f0,options);
    unknown_chat_a72cfc->unknown_slot15(options);
}
