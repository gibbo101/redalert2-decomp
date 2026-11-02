#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
#include "shared/rules.hpp"
#include "shared/crt_string.hpp"
extern "C" int __cdecl _wcsnicmp(wchar_t const *,wchar_t const *,unsigned);
extern "C" int __cdecl wcsncmp(wchar_t const *,wchar_t const *,unsigned);
extern "C" int __cdecl _wcsicmp(wchar_t const *,wchar_t const *);
int unknown_scheme_index_4cefc0();
extern char wol_source_file_007fd62c[];
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
extern char wol_reply_observer_label_007fe964[];
extern wchar_t wol_reply_space_007d64f4[];
// @ref ?wol_reply_observer_label_007fe964@@3PADA=007fe964
// @ref ?wol_reply_space_007d64f4@@3PAGA=007d64f4
// @ref __wcsnicmp=007970a0
// @ref _wcsncmp=007846cc
// @ref __wcsicmp=00796318
// @ref ?unknown_scheme_index_4cefc0@@YAHXZ=004cefc0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?Add_Message@MessageListClass@@QAEPAVTextLabelClass@@PBGH0HIH_N@Z=005b4da0
extern char wol_page_label_007dfc7c[];
// @ref ?wol_page_label_007dfc7c@@3PADA=007dfc7c
int __fastcall Parse_Page_Command_00746480(wchar_t const *text)
{
    int result=0;
    wchar_t nickname[16];
    WOL::User recipient;
    wchar_t command[128];
    wcscpy(command,StringTable::Load_String(wol_page_label_007dfc7c,0,wol_source_file_007fd62c,0x293f));
    if(_wcsnicmp(text,command,wcslen(command))==0) {
        int name_length=0;
        unsigned length=wcslen(text)+1;
        wchar_t *copy=(wchar_t *)operator new(length*2);
        if(!copy) return 0;
        copy=wcsncpy(copy,text,length);
        if(!copy) return 0;
        wchar_t *message=copy+wcslen(command);
        while(*message && wcsncmp(message,wol_reply_space_007d64f4,1)==0) ++message;
        while(*message) {
            if(wcsncmp(message,wol_reply_space_007d64f4,1)==0 || name_length>10) break;
            nickname[name_length++]=*message++;
        }
        nickname[name_length]=0;
        while(*message && wcsncmp(message,wol_reply_space_007d64f4,1)==0) ++message;
        if(name_length>10) {
            result=1;
        } else if(name_length==0) {
            result=1;
        } else {
            bool recipient_is_player=false;
            if(unknown_int_a3d548) {
                for(int i=0;i<unknown_players_a3fa7c.Count();++i) {
                    if(_wcsicmp(unknown_players_a3fa7c[i]->Name,nickname)==0) {
                        recipient_is_player=true;
                        break;
                    }
                }
            }
            if(!recipient_is_player) {
                if(wcslen(message)>0) {
                    strcpy(recipient.name,Unknown_006FA120(nickname));
                    unknown_chat_a72cfc->unknown_slot62(&recipient,message);
                }
                result=1;
            } else {
                int color=unknown_scheme_index_4cefc0();
                unknown_session_a3d298.Messages.Add_Message(0,0,
                StringTable::Load_String(wol_reply_observer_label_007fe964,0,wol_source_file_007fd62c,0x297b),
                color,0x16,(int)(Rules->MessageDelay*900.0),false);
                result=2;
            }
        }
        operator delete(copy);
    }
    return result;
}
