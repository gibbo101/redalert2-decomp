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
extern char wol_reply_label_007dfc14[];
extern char wol_reply_short_label_007dfbfc[];
extern char wol_reply_empty_label_007fe97c[];
extern char wol_reply_observer_label_007fe964[];
extern wchar_t wol_reply_space_007d64f4[];
// @ref ?wol_reply_label_007dfc14@@3PADA=007dfc14
// @ref ?wol_reply_short_label_007dfbfc@@3PADA=007dfbfc
// @ref ?wol_reply_empty_label_007fe97c@@3PADA=007fe97c
// @ref ?wol_reply_observer_label_007fe964@@3PADA=007fe964
// @ref ?wol_reply_space_007d64f4@@3PAGA=007d64f4
// @ref __wcsnicmp=007970a0
// @ref _wcsncmp=007846cc
// @ref __wcsicmp=00796318
// @ref ?unknown_scheme_index_4cefc0@@YAHXZ=004cefc0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?Add_Message@MessageListClass@@QAEPAVUnknownMessageNode@@PBGH0HIH_N@Z=005b4da0
int __fastcall Reply_To_Last_Pager_007466c0(wchar_t const *text)
{
    int result=0;
    wchar_t reply_command[128];
    WOL::User recipient;
    wchar_t short_command[128];
    wchar_t notice[128];
    wcscpy(reply_command,StringTable::Load_String(wol_reply_label_007dfc14,0,wol_source_file_007fd62c,0x298f));
    wcscpy(short_command,StringTable::Load_String(wol_reply_short_label_007dfbfc,0,wol_source_file_007fd62c,0x2990));
    if(_wcsnicmp(text,reply_command,wcslen(reply_command))==0 ||
    wcsncmp(text,short_command,wcslen(short_command))==0) {
        unsigned length=wcslen(text)+1;
        wchar_t *copy=(wchar_t *)operator new(length*2);
        if(!copy) return 0;
        copy=wcsncpy(copy,text,length);
        if(!copy) return 0;
        wchar_t *message;
        if(wcsncmp(text,reply_command,wcslen(reply_command))==0) message=copy+wcslen(reply_command);
        else message=copy+wcslen(short_command);
        while(*message && wcsncmp(message,wol_reply_space_007d64f4,1)==0) ++message;
        bool recipient_is_player=false;
        if(unknown_int_a3d548) {
            for(int i=0;i<unknown_players_a3fa7c.Count();++i) {
                if(_wcsicmp(unknown_players_a3fa7c[i]->Name,Unknown_006FA180(unknown_last_pager_b2ac48))==0) {
                    recipient_is_player=true;
                    break;
                }
            }
        }
        if(!recipient_is_player) {
            if(strlen(unknown_last_pager_b2ac48)>0) {
                if(wcslen(message)>0) {
                    strcpy(recipient.name,unknown_last_pager_b2ac48);
                    unknown_chat_a72cfc->unknown_slot62(&recipient,message);
                }
                result=1;
            } else {
                wcscpy(notice,StringTable::Load_String(wol_reply_empty_label_007fe97c,0,wol_source_file_007fd62c,0x29c3));
                HWND window=Unknown_00735B10();
                if(window) {
                    if(GetDlgItem(window,0x53f)) Unknown_005C2C80(unknown_color_7a7360,notice);
                    if(GetDlgItem(window,0x5b5)) Unknown_005c2d10(unknown_color_7a7360,notice);
                }
                if(unknown_session_a3d298.Unknown_00672F10()) {
                    int color=unknown_scheme_index_4cefc0();
                    unknown_session_a3d298.Messages.Add_Message(0,0,notice,
                    color,0x16,(int)(Rules->MessageDelay*900.0),false);
                }
                result=2;
            }
        } else {
            int color=unknown_scheme_index_4cefc0();
            unknown_session_a3d298.Messages.Add_Message(0,0,
            StringTable::Load_String(wol_reply_observer_label_007fe964,0,wol_source_file_007fd62c,0x29db),
            color,0x16,(int)(Rules->MessageDelay*900.0),false);
            result=2;
        }
        operator delete(copy);
    }
    return result;
}
