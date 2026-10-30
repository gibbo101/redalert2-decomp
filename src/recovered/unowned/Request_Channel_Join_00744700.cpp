#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern char wol_leave_debug_7fe6f8[],wol_join_debug_7fe71c[];
extern char wol_source_file_007fd62c[],wol_leaving_label_7fe6e4[];
void __fastcall Open_Wait_Window_0074d4d0(unsigned int,WideString const &,bool);
// @ref ?wol_leave_debug_7fe6f8@@3PADA=007fe6f8
// @ref ?wol_join_debug_7fe71c@@3PADA=007fe71c
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_leaving_label_7fe6e4@@3PADA=007fe6e4
// @ref ?Open_Wait_Window_0074d4d0@@YIXIABVWideString@@_N@Z=0074d4d0
int __fastcall Request_Channel_Join_00744700(WOL::Channel *channel,Wstring const &password,WideString title)
{
    char const *name=channel->name;
    if(strcmp(name,unknown_game_channel_b299c0.name) && strcmp(name,unknown_pending_channel_b26a60.name)) {
        if(unknown_b2abe8) {
            Debug_Printf(wol_leave_debug_7fe6f8,unknown_game_channel_b299c0.name,unknown_game_channel_b299c0.unknown_00);
            unknown_chat_a72cfc->unknown_slot09();
            {
                WideString leaving(StringTable::Load_String(wol_leaving_label_7fe6e4,0,wol_source_file_007fd62c,0x24a3));
                Open_Wait_Window_0074d4d0(0x40,leaving,true);
            }
            for(int i=0;unknown_b2abe8 && i<150;++i) {
                Sleep(100);
                Unknown_0073e100();
            }
            void *wait=Unknown_00735940(0xc4);
            if(wait && !(unknown_b2abe0&=~0x40)) Unknown_007357E0(wait,0);
            HWND current=Unknown_00735B10();
            HWND edit=GetDlgItem(current,0x540);
            if(edit) SetFocus(edit);
            if(unknown_b2abe8) return 1;
        }
        strcpy(channel->key,password.Peek_Buffer());
        unknown_pending_channel_b26a60=*channel;
        {
            WideString message(title.unknown_text_770430());
            Open_Wait_Window_0074d4d0(2,message,false);
        }
        Debug_Printf(wol_join_debug_7fe71c,name);
        return unknown_chat_a72cfc->unknown_slot08(channel);
    }
    return 0;
}
