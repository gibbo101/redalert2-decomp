#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/win32_window.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/crt_string.hpp"
extern HANDLE wol_wait_events_b264f8[18];
extern bool connection_wait_callback_0073c120();
void __fastcall Open_Wait_Window_0074d4d0(unsigned int,WideString const &,bool);
inline void __fastcall Close_Wonline_Wait(unsigned int);
void __stdcall unknown_dialog_5ecf40(HWND,int);
long __stdcall Birthdate_Dialog_007494d0(HWND,UINT,WPARAM,LPARAM);
long __stdcall Account_Details_Dialog_007498e0(HWND,UINT,WPARAM,LPARAM);
extern Wstring unknown_wstring_b29ce4;
extern int account_birth_year_b2a6d4,account_birth_day_b26930,account_birth_month_b26894,account_newsletter_b29098;
extern Wstring account_name_b2a640,account_password_b2a71c,account_password_check_b2a724,unknown_account_detail_b2945c;
extern int unknown_account_checkbox_b29ad0;
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?connection_wait_callback_0073c120@@YA_NXZ=0073c120
// @ref ?unknown_dialog_5ecf40@@YGXPAUHWND__@@H@Z=005ecf40
// @ref ?Birthdate_Dialog_007494d0@@YGJPAUHWND__@@IIJ@Z=007494d0
// @ref ?account_birth_year_b2a6d4@@3HA=00b2a6d4
// @ref ?account_birth_day_b26930@@3HA=00b26930
// @ref ?account_birth_month_b26894@@3HA=00b26894
// @ref ?account_newsletter_b29098@@3HA=00b29098
extern char wol_source_file_007fd62c[];
extern char account_text_7fe82c[];
// @ref ?account_text_7fe82c@@3PADA=007fe82c
extern char account_text_7fe814[];
// @ref ?account_text_7fe814@@3PADA=007fe814
extern char account_text_7fe808[];
// @ref ?account_text_7fe808@@3PADA=007fe808
extern char account_text_7fe800[];
// @ref ?account_text_7fe800@@3PADA=007fe800
extern char account_text_7fd740[];
// @ref ?account_text_7fd740@@3PADA=007fd740
extern char account_text_7fe7e8[];
// @ref ?account_text_7fe7e8@@3PADA=007fe7e8
extern char account_text_7fe7d4[];
// @ref ?account_text_7fe7d4@@3PADA=007fe7d4
extern char account_text_7fe7bc[];
// @ref ?account_text_7fe7bc@@3PADA=007fe7bc
extern char account_text_7fe780[];
// @ref ?account_text_7fe780@@3PADA=007fe780
extern char account_text_7fe76c[];
// @ref ?account_text_7fe76c@@3PADA=007fe76c
extern char account_text_7fe754[];
// @ref ?account_text_7fe754@@3PADA=007fe754
extern char account_text_7fe744[];
// @ref ?account_text_7fe744@@3PADA=007fe744
void __fastcall Create_Wonline_Account_00744a00(HWND parent)
{
    OwnerDraw::unknown_5e5150(parent,false);
    unknown_5159b0(0,true);
    char nickname[32];
    char password[32];
    char confirmation[32];
    char email[128];
    char parent_email[128];
    int newsletter,day,year,month,share_info;
    HWND dialog;
    newsletter=1;
    month=1;
    day=0;
    year=0;
    for(int event_index=0;event_index<18;++event_index) ResetEvent(wol_wait_events_b264f8[event_index]);
    memset(nickname,0,sizeof(nickname));
    memset(password,0,sizeof(password));
    memset(confirmation,0,sizeof(confirmation));
    memset(email,0,sizeof(email));
    memset(parent_email,0,sizeof(parent_email));
    {
        WideString message(StringTable::Load_String(account_text_7fe82c,0,wol_source_file_007fd62c,0x251d));
        Open_Wait_Window_0074d4d0(0x80,message,false);
    }
    Debug_Printf(account_text_7fe814);
    unknown_chat_a72cfc->Request_Server_List(unknown_protocol_7fd370,0x10006,account_text_7fe800,account_text_7fe808,35);
    DWORD event;
    do {
        event=WaitForMultipleObjects(18,wol_wait_events_b264f8,false,100);
        while(event==0x102) {
            Unknown_0073e100();
            event=WaitForMultipleObjects(18,wol_wait_events_b264f8,false,100);
        }
        ResetEvent(wol_wait_events_b264f8[event]);
    } while(event!=0 && event!=1);
    Close_Wonline_Wait(~0u);
    if(event==0) {
        ShowWindow(parent,5);
        unknown_dialog_5ecf40(parent,0);
        return;
    }
    if(event==8) {
        SetEvent(wol_wait_events_b264f8[8]);
        ShowWindow(parent,5);
        unknown_dialog_5ecf40(parent,0);
        return;
    }
birthdate_retry:
    unknown_5159b0(0,true);
    {
        dialog=(HWND)unknown_create_dialog_735700(ProgramInstance,0xe7,MainWindow,(UnknownDialogProc)Birthdate_Dialog_007494d0,0);
        unknown_show_dialog_5ff7e0(dialog,0xe7);
        SendDlgItemMessageA(dialog,0x62e,0x14e,month-1,0);
        if(day>0) {
            Wstring text=Wstring_From_Integer(day);
            char const *number=text.Get();
            HWND edit=GetDlgItem(dialog,0x62f);
            SendMessageA(edit,0x4b4,0,(LPARAM)number);
        } else {
            HWND edit=GetDlgItem(dialog,0x62f);
            SendMessageA(edit,0x4b4,0,(LPARAM)unknown_string_83c55c);
        }
        if(year>0) {
            Wstring text=Wstring_From_Integer(year);
            char const *number=text.Get();
            HWND edit=GetDlgItem(dialog,0x630);
            SendMessageA(edit,0x4b4,0,(LPARAM)number);
        } else {
            HWND edit=GetDlgItem(dialog,0x630);
            SendMessageA(edit,0x4b4,0,(LPARAM)unknown_string_83c55c);
        }
        SendDlgItemMessageA(dialog,0x626,0x4b4,0,(LPARAM)email);
        SendDlgItemMessageA(dialog,0x631,0xf1,newsletter,0);
        ShowWindow(parent,0);
        ShowWindow(dialog,1);
        if(Unknown_007359e0(dialog,connection_wait_callback_0073c120,0,1,1)==1) {
            email[0]=0;
            strcpy(email,unknown_wstring_b29ce4.Get());
            month=account_birth_month_b26894+1;
            day=account_birth_day_b26930;
            year=account_birth_year_b2a6d4;
            newsletter=account_newsletter_b29098;
            if(month<=0 || day<=0 || year<=0 || strlen(email)<6) {
                Message_Box_005c3230(StringTable::Load_String(account_text_7fe7d4,0,wol_source_file_007fd62c,0x257b),0,connection_wait_callback_0073c120,false);
                goto birthdate_retry;
            }
            unknown_b2ac70=0;
            unknown_b2ac6c=-1;
            if(unknown_ladder_client_a72d00->Request_Age_Check(month,day,year,email)!=0) {
                Message_Box_005c3230(StringTable::Load_String(account_text_7fd740,0,wol_source_file_007fd62c,0x2583),0,connection_wait_callback_0073c120,false);
                goto account_retry;
            }
            {
                WideString message(StringTable::Load_String(account_text_7fe7e8,0,wol_source_file_007fd62c,0x2586));
                Open_Wait_Window_0074d4d0(0x100,message,true);
            }
            if(unknown_b2ac6c<0) {
                if(unknown_b2ac0c==(int)0x80040100)
                Message_Box_005c3230(StringTable::Load_String(account_text_7fe7d4,0,wol_source_file_007fd62c,0x258a),0,connection_wait_callback_0073c120,false);
                else
                Message_Box_005c3230(StringTable::Load_String(account_text_7fd740,0,wol_source_file_007fd62c,0x258c),0,connection_wait_callback_0073c120,false);
                goto birthdate_retry;
            }
            if(unknown_b2ac6c<13 && !unknown_b2ac70) {
                if(Message_Box_005c3230(StringTable::Load_String(account_text_7fe7bc,0,wol_source_file_007fd62c,0x2595),4,connection_wait_callback_0073c120,false)==6) {
                    char url[256];
                    sprintf(url,account_text_7fe780,unknown_b2ac5c);
                    unknown_open_url_73c580(url,1);
                }
                goto birthdate_retry;
            }
account_retry:
            {
                int resource;
                if(unknown_b2ac6c<13) resource=0xe6;
                else resource=unknown_b2ac6c>=18 ? 0xf4 : 0xf3;
                dialog=(HWND)unknown_create_dialog_735700(ProgramInstance,resource,MainWindow,(UnknownDialogProc)Account_Details_Dialog_007498e0,0);
                unknown_show_dialog_5ff7e0(dialog,resource);
                if(nickname && strlen(nickname)>0) {
                    HWND edit=GetDlgItem(dialog,0x628);
                    SendMessageA(edit,0x4b4,0,(LPARAM)nickname);
                } else {
                    HWND edit=GetDlgItem(dialog,0x628);
                    SendMessageA(edit,0x4b4,0,(LPARAM)unknown_string_83c55c);
                }
                if(parent_email && strlen(parent_email)>0) {
                    HWND edit=GetDlgItem(dialog,0x5e5);
                    SendMessageA(edit,0x4b4,0,(LPARAM)parent_email);
                } else {
                    HWND edit=GetDlgItem(dialog,0x5e5);
                    SendMessageA(edit,0x4b4,0,(LPARAM)unknown_string_83c55c);
                }
                if(password && strlen(password)>0) {
                    HWND edit=GetDlgItem(dialog,0x72c);
                    SendMessageA(edit,0x4b4,0,(LPARAM)password);
                } else {
                    HWND edit=GetDlgItem(dialog,0x72c);
                    SendMessageA(edit,0x4b4,0,(LPARAM)unknown_string_83c55c);
                }
                if(confirmation && strlen(confirmation)>0) {
                    HWND edit=GetDlgItem(dialog,0x627);
                    SendMessageA(edit,0x4b4,0,(LPARAM)confirmation);
                } else {
                    HWND edit=GetDlgItem(dialog,0x627);
                    SendMessageA(edit,0x4b4,0,(LPARAM)unknown_string_83c55c);
                }
                ShowWindow(dialog,1);
                SendMessageA(dialog,0x4a9,0,1);
                if(Unknown_007359e0(dialog,connection_wait_callback_0073c120,0,1,1)!=1) goto birthdate_retry;
                nickname[0]=0;
                strcpy(nickname,account_name_b2a640.Get());
                password[0]=0;
                strcpy(password,account_password_b2a71c.Get());
                confirmation[0]=0;
                strcpy(confirmation,account_password_check_b2a724.Get());
                parent_email[0]=0;
                if(resource==0xf3) strcpy(parent_email,unknown_account_detail_b2945c.Get());
                share_info=0;
                if(resource==0xf4) share_info=unknown_account_checkbox_b29ad0;
                if(strcmp(password,confirmation)) {
                    Message_Box_005c3230(StringTable::Load_String(account_text_7fe76c,0,wol_source_file_007fd62c,0x25ff),0,connection_wait_callback_0073c120,false);
                    goto account_retry;
                }
                if(strlen(password)!=8) {
                    Message_Box_005c3230(StringTable::Load_String(account_text_7fe754,0,wol_source_file_007fd62c,0x2604),0,connection_wait_callback_0073c120,false);
                    goto account_retry;
                }
                if(unknown_ladder_client_a72d00->Request_New_Nick(nickname,password,email,parent_email,newsletter,share_info)!=0) {
                    Message_Box_005c3230(StringTable::Load_String(account_text_7fd740,0,wol_source_file_007fd62c,0x2609),0,connection_wait_callback_0073c120,false);
                } else {
                    {
                        WideString message(StringTable::Load_String(account_text_7fe744,0,wol_source_file_007fd62c,0x260b));
                        Open_Wait_Window_0074d4d0(0x100,message,true);
                    }
                    if(unknown_newnick_result_b2ac08<0) goto account_retry;
                }
            }
            ShowWindow(parent,5);
            unknown_dialog_5ecf40(parent,0);
            return;
        } else {
            ShowWindow(parent,1);
        }
    }
    ShowWindow(parent,5);
    unknown_dialog_5ecf40(parent,0);
}
