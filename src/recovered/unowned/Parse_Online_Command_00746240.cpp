#include "shared/wol_sink.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
#include "shared/session_state.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_player_entry.hpp"
int unknown_scheme_index_4cefc0();
extern "C" int __cdecl wcsncmp(wchar_t const *,wchar_t const *,unsigned int);
extern char online_command_label_007fe950[],missing_name_label_007fe944[],wol_source_file_007fd62c[];
extern char online_last_name_00b29cd8[];
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref _wcsncmp=007846cc
// @ref ?online_command_label_007fe950@@3PADA=007fe950
// @ref ?missing_name_label_007fe944@@3PADA=007fe944
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?online_last_name_00b29cd8@@3PADA=00b29cd8
// @ref ?unknown_scheme_index_4cefc0@@YAHXZ=004cefc0
// @ref ?Add_Message@MessageListClass@@QAEPAVTextLabelClass@@PBGH0HIH_N@Z=005b4da0
int __fastcall Parse_Online_Command_00746240(wchar_t const *text)
{
    int handled=0;
    wchar_t command[64];
    wcscpy(command,StringTable::Load_String(online_command_label_007fe950,0,wol_source_file_007fd62c,0x2909));
    if(wcsncmp(text,command,wcslen(command))==0) {
    int count=0;
    wchar_t const *cursor=text+wcslen(command);
    while(wcsncmp(cursor,L" ",1)==0) ++cursor;
    wchar_t name[16];
    while(*cursor) {
        if(wcsncmp(cursor,L" ",1)==0 || count>=10) break;
        name[count++]=*cursor++;
    }
    name[count]=0;
    if(wcslen(name)>0) {
    WOL::User user;
    strcpy(user.name,Unknown_006FA120((unsigned short const *)name));
    strcpy(online_last_name_00b29cd8,Unknown_006FA120((unsigned short const *)name));
    unknown_chat_a72cfc->unknown_slot24(&user);
    handled=1;
    } else {
        wchar_t message[256];
        swprintf(message,StringTable::Load_String(missing_name_label_007fe944,0,wol_source_file_007fd62c,0x291d));
        HWND window=Unknown_00735B10();
        if(window) {
            if(GetDlgItem(window,0x53f)) Unknown_005C2C80(unknown_color_7a7360,(unsigned short const *)message);
            if(GetDlgItem(window,0x5b5)) Unknown_005c2d10(unknown_color_7a7360,(unsigned short const *)message);
        }
        if(unknown_session_a3d298.Unknown_00672F10()) {
            int color=unknown_scheme_index_4cefc0();
            unknown_session_a3d298.Messages.Add_Message(0,0,(unsigned short const *)message,color,0x16,Rules->MessageDelay*900,false);
        }
        handled=1;
    }
    }
    return handled;
}
