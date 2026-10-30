#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
extern char wol_leave_debug_7fe6f8[],wol_source_file_007fd62c[],wol_leaving_label_7fe6e4[];
void __fastcall Open_Wait_Window_0074d4d0(unsigned int,WideString const &,bool);
// @ref ?wol_leave_debug_7fe6f8@@3PADA=007fe6f8
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_leaving_label_7fe6e4@@3PADA=007fe6e4
// @ref ?Open_Wait_Window_0074d4d0@@YIXIABVWideString@@_N@Z=0074d4d0
bool __fastcall Leave_Current_Channel_00744610(unsigned int flags,bool show)
{
    if(unknown_b2abe8) {
        Debug_Printf(wol_leave_debug_7fe6f8,unknown_game_channel_b299c0.name,unknown_game_channel_b299c0.unknown_00);
        unknown_chat_a72cfc->unknown_slot09();
        {
            WideString title(StringTable::Load_String(wol_leaving_label_7fe6e4,0,wol_source_file_007fd62c,0x24a3));
            Open_Wait_Window_0074d4d0(flags,title,show);
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
    }
    return unknown_b2abe8==0;
}
