#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
LRESULT __fastcall unknown_get_window_text(HWND,Wstring &);
LRESULT __fastcall unknown_get_window_wide_text(HWND,WideString &);
WideString __fastcall Limit_Name_Text_005ccf50(HWND);
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
bool __fastcall Unknown_005def80(long,bool);
extern int unknown_color_7a737c;
extern unsigned short wol_empty_text_839d4c[];
extern unsigned short wol_page_echo_007fe9a4[];
extern char wol_name_error_007e6c90[],wol_enter_message_007fe9e8[],wol_no_squad_007fe998[];
extern char wol_reply_observer_label_007fe964[],wol_source_file_007fd62c[],wol_squad_user_007e1a60[];
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?wol_empty_text_839d4c@@3PAGA=00839d4c
// @ref ?wol_page_echo_007fe9a4@@3PAGA=007fe9a4
// @ref ?wol_name_error_007e6c90@@3PADA=007e6c90
// @ref ?wol_enter_message_007fe9e8@@3PADA=007fe9e8
// @ref ?wol_no_squad_007fe998@@3PADA=007fe998
// @ref ?wol_squad_user_007e1a60@@3PADA=007e1a60
// @ref ?unknown_color_7a737c@@3HA=007a737c
long __stdcall Find_Page_Dialog_007485d0(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    long result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(result) return result;
    switch(message) {
    case 0x111:
        switch((int)(wparam&0xffff)) {
        case 2:
            Unknown_007357E0(window,2);
            return 0;
        case 0x5c1: {
            Wstring name;
            unknown_get_window_text((HWND)lparam,name);
            WideString text;
            unknown_get_window_wide_text(GetDlgItem(window,0x540),text);
            BOOL enabled=(name.Length()>0 && text.Length()>0)?1:0;
            EnableWindow(GetDlgItem(window,0x5c2),enabled);
            return 0;
        }
        case 0x5c2: {
            HWND edit=GetDlgItem(window,0x540);
            WideString text=Limit_Name_Text_005ccf50(edit);
            SendMessageA(edit,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
            EnableWindow(GetDlgItem(window,0x5c2),false);
            SetFocus(edit);
            if(!unknown_chat_a72cfc) return 0;
            Wstring name;
            unknown_get_window_text(GetDlgItem(window,0x5c1),name);
            name.Truncate(9);
            WOL::User user;
            strcpy(user.name,name.Get());
            if(text.Length()>0 && strlen(user.name)>0) {
                bool recipient_is_player=false;
                if(unknown_int_a3d548) {
                    for(int i=0;i<unknown_players_a3fa7c.Count();++i) {
                        NodeNameType *player=unknown_players_a3fa7c[i];
                        if(_stricmp(Unknown_006FA120(player->Name),user.name)==0) {
                            recipient_is_player=true;
                            break;
                        }
                    }
                }
                if(!recipient_is_player) {
                    unknown_chat_a72cfc->unknown_slot62(&user,text.Get());
                    Unknown_005c2d10(unknown_color_7a737c,wol_page_echo_007fe9a4,unknown_wstring_b26cb8.Buffer,text.Get());
                } else {
                    Unknown_005c2d10(-1,StringTable::Load_String(wol_reply_observer_label_007fe964,0,wol_source_file_007fd62c,0x30ed));
                }
            } else if(strlen(user.name)==0) {
                Unknown_005c2d10(-1,StringTable::Load_String(wol_name_error_007e6c90,0,wol_source_file_007fd62c,0x30f9));
            } else {
                Unknown_005c2d10(-1,StringTable::Load_String(wol_enter_message_007fe9e8,0,wol_source_file_007fd62c,0x30fb));
            }
            return 0;
        }
        case 0x5c3:
            if(unknown_chat_a72cfc) {
                char name[64];
                memset(name,0,sizeof(name));
                SendDlgItemMessageA(window,0x5c1,0x4b5,60,(LPARAM)name);
                name[9]=0;
                WOL::User user;
                strcpy(user.name,name);
                if(strlen(user.name)>0) unknown_chat_a72cfc->unknown_slot24(&user);
                else Unknown_005c2d10(-1,StringTable::Load_String(wol_name_error_007e6c90,0,wol_source_file_007fd62c,0x30bb));
            }
            break;
        case 0x607:
            if(unknown_chat_a72cfc) {
                if(unknown_squad_id_b2abfc==0) {
                    Unknown_005c2d10(-1,StringTable::Load_String(wol_no_squad_007fe998,0,wol_source_file_007fd62c,0x3107));
                    break;
                } else {
                    WideString text;
                    HWND edit=GetDlgItem(window,0x540);
                    unknown_get_window_wide_text(edit,text);
                    SendMessageA(edit,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
                    SetFocus(edit);
                    WOL::User user;
                    strcpy(user.name,wol_squad_user_007e1a60);
                    if(text.Length()>0) unknown_chat_a72cfc->unknown_slot62(&user,text.Get());
                    else Unknown_005c2d10(-1,StringTable::Load_String(wol_enter_message_007fe9e8,0,wol_source_file_007fd62c,0x311a));
                }
            }
            break;
        }
        break;
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
        return 0;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x497: {
        SendDlgItemMessageA(window,0x5c1,0xc5,9,0);
        HWND name_edit=GetDlgItem(window,0x5c1);
        SendMessageA(name_edit,0x4d1,1,0);
        name_edit=GetDlgItem(window,0x5c1);
        SendMessageA(name_edit,0x4b4,0,(LPARAM)unknown_string_83c55c);
        if(unknown_timer_b292e8.Value()>0) {
            name_edit=GetDlgItem(window,0x5c1);
            SendMessageA(name_edit,0x4b4,0,(LPARAM)unknown_last_pager_b2ac48);
            SetFocus(GetDlgItem(window,0x540));
            unknown_timer_b292e8=CDTimerClass<SystemTimerClass>(0);
        }
        break;
    }
    case 0x4da:
        PostMessageA(GetDlgItem(window,0x5c2),0xf5,0,0);
        break;
    case 0x4db:
        Unknown_005def80(lparam,wparam!=0);
        return 0;
    case 0x540: {
        WideString text=Limit_Name_Text_005ccf50((HWND)lparam);
        Wstring name;
        unknown_get_window_text(GetDlgItem(window,0x5c1),name);
        BOOL enabled=(text.Length()>0 && name.Length()>0)?1:0;
        EnableWindow(GetDlgItem(window,0x5c2),enabled);
        return 0;
    }
    }
    return 0;
}
