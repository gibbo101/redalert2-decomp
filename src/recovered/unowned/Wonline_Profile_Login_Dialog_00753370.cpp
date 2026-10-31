#include "shared/wol_sink.hpp"
#include "shared/wonline_dialog_control.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/crt_string.hpp"
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
void __stdcall unknown_dialog_5ecf40(HWND,int);
void __fastcall unknown_reset_combo_6007f0(HWND);
LRESULT __fastcall unknown_get_window_text(HWND,Wstring &);
LRESULT __fastcall unknown_get_combo_item_wide_text(HWND,WPARAM,WideString &);
void __fastcall Unknown_00753240(HWND);
bool __fastcall Populate_Server_Choices_007454c0(HWND,bool);
void __fastcall Unknown_00739a50(HWND,char);
void __fastcall Create_Wonline_Account_00744a00(HWND);
void __fastcall View_HTML_0073c580(char const *,int);
Wstring __fastcall WOL_Auto_Login_Persona();
Wstring __fastcall WOL_Last_Valid_Persona();
void __fastcall WOL_Set_Auto_Login_Persona(Wstring const &);
void __fastcall WOL_Set_Last_Valid_Persona(Wstring const &);
extern int unknown_online_option_a3d2a8,profile_url_value_b2ac5c;
extern char profile_help_url_7fd564[],profile_registration_url_7fd5a4[],profile_choose_nick_7fd2f0[],wol_source_file_007fd62c[];
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?unknown_dialog_5ecf40@@YGXPAUHWND__@@H@Z=005ecf40
// @ref ?unknown_reset_combo_6007f0@@YIXPAUHWND__@@@Z=006007f0
// @ref ?unknown_get_window_text@@YIJPAUHWND__@@AAVWstring@@@Z=00600df0
// @ref ?unknown_get_combo_item_wide_text@@YIJPAUHWND__@@IAAVWideString@@@Z=00600fd0
// @ref ?Unknown_00739a50@@YIXPAUHWND__@@D@Z=00739a50
// @ref ?profile_help_url_7fd564@@3PADA=007fd564
// @ref ?profile_registration_url_7fd5a4@@3PADA=007fd5a4
// @ref ?profile_choose_nick_7fd2f0@@3PADA=007fd2f0
// @ref ?profile_url_value_b2ac5c@@3HA=00b2ac5c
// @ref ?unknown_online_option_a3d2a8@@3HA=00a3d2a8
// @ref ??_7?$rc_ptr@VPlayerProfile@@@@6B@=007af54c
long __stdcall Wonline_Profile_Login_Dialog_00753370(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    if(message==0x110 && lparam) SetWindowLongA(window,8,*(long *)(lparam+4));
    long result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(result) return result;
    OwnerDraw::DialogControl *control=(OwnerDraw::DialogControl *)GetWindowLongA(window,8);
    switch(message) {
    case 0xf:
        Unknown_005FEE70(window);unknown_dialog_5e5f20(window);ValidateRect(window,0);
    painted:return 1;
    case 0x14:goto painted;
    case 0x2b:Unknown_005FE380(lparam);return 1;
    case 0x111:
        switch(wparam&0xffff) {
        case 0x687:
            unknown_a3d2a4=4;unknown_online_option_a3d2a8=5;
            control->Set_Window_006010f0((unsigned)window,(HWND)0x687);return 0;
        case 0x688:View_HTML_0073c580(profile_help_url_7fd564,0);return 0;
        case 0x686:
            unknown_a3d2a4=0;control->Set_Window_006010f0((unsigned)window,(HWND)0x686);return 0;
        case 0x628:
            switch((unsigned short)(wparam>>16)) { case 1: {
                HWND automatic=GetDlgItem(window,0x6ff);
                SendMessageA(automatic,0x49d,0,1);ShowWindow(automatic,0);
                int selected=SendMessageA((HWND)lparam,0x147,0,0);
                int nick_index=-1;
                if(selected!=-1) nick_index=SendMessageA((HWND)lparam,0x150,selected,0);
                unknown_wstring_b26cb8.Release();
                if(nick_index!=-1) {
                    char const *nickname=0,*password=0;
                    if(unknown_chat_a72cfc->unknown_slot36(nick_index,&nickname,&password)==0) unknown_wstring_b26cb8=nickname;
                }
                rc_ptr<PlayerProfile> profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
                Wstring automatic_persona=WOL_Auto_Login_Persona();
                EnableWindow(automatic,nick_index!=-1);
                SendMessageA(automatic,0xf1,(automatic_persona==unknown_wstring_b26cb8)?1:0,0);
                SendMessageA(automatic,0x49d,0,0);ShowWindow(automatic,5);InvalidateRect(automatic,0,0);
                if(profile.Get()) profile->Populate_Dialog_00739b70(window,unknown_wstring_b26cb8,false);
                EnableWindow(GetDlgItem(window,0x6eb),nick_index!=-1 && unknown_wstring_b26cb8.Length()>0);
                EnableWindow(GetDlgItem(window,0x687),nick_index!=-1 && unknown_wstring_b26cb8.Length()>0);
            } break; }
            break;
        case 0x629:
            switch((unsigned short)(wparam>>16)) { case 1: {
                Wstring server;unknown_get_window_text((HWND)lparam,server);
                rc_ptr<PlayerProfile> profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
                if(profile.Get()) {profile->Set_Server_00739920(server);profile->Save_007395d0(unknown_wstring_b26cb8);}
            } break; }
            break;
        case 0x62a:
            switch((unsigned short)(wparam>>16)) { case 1: {
                int locale=0;int selected=SendMessageA((HWND)lparam,0x147,0,0);
                if(selected!=-1) locale=SendMessageA((HWND)lparam,0x150,selected,0);
                rc_ptr<PlayerProfile> profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
                if(profile.Get()) {profile->Set_Locale_00739950(locale,3);profile->Save_007395d0(unknown_wstring_b26cb8);}
            } break; }
            break;
        case 0x6a1:
            switch((unsigned short)(wparam>>16)) { case 1: {
                int value=-2;int selected=SendMessageA((HWND)lparam,0x147,0,0);
                if(selected!=-1) value=SendMessageA((HWND)lparam,0x150,selected,0);
                rc_ptr<PlayerProfile> profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
                if(profile.Get()) {profile->Set_Country_007399b0(value);profile->Save_007395d0(unknown_wstring_b26cb8);}
            } break; }
            break;
        case 0x6a2:
            switch((unsigned short)(wparam>>16)) { case 1: {
                int value=-2;int selected=SendMessageA((HWND)lparam,0x147,0,0);
                if(selected!=-1) value=SendMessageA((HWND)lparam,0x150,selected,0);
                rc_ptr<PlayerProfile> profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
                if(profile.Get()) {profile->Set_Color_007399d0(value);profile->Save_007395d0(unknown_wstring_b26cb8);}
            } break; }
            break;
        case 0x6ff:
            if(SendMessageA((HWND)lparam,0xf0,0,0)==1) WOL_Set_Auto_Login_Persona(unknown_wstring_b26cb8);
            else {
                Wstring automatic=WOL_Auto_Login_Persona();
                if(automatic.As_Lower()==unknown_wstring_b26cb8.As_Lower()) WOL_Set_Auto_Login_Persona(unknown_string_83c55c);
            }
            break;
        case 0x6ea:Create_Wonline_Account_00744a00(window);return 0;
        case 0x6eb: {
            HWND nicknames=GetDlgItem(window,0x628);
            int selected=SendMessageA(nicknames,0x147,0,0);
            if(selected!=-1) {
                WideString wide;unknown_get_combo_item_wide_text(nicknames,selected,wide);
                Wstring nickname=Narrow_Copy_00771280(wide);nickname.To_Lower();
                Wstring automatic=WOL_Auto_Login_Persona();
                if(nickname==automatic.As_Lower()) WOL_Set_Auto_Login_Persona(unknown_string_83c55c);
                Wstring last=WOL_Last_Valid_Persona();
                if(nickname==last.As_Lower()) WOL_Set_Last_Valid_Persona(unknown_string_83c55c);
                int nick_index=SendMessageA(nicknames,0x150,selected,0);
                if(nick_index!=-1) {
                    unknown_chat_a72cfc->unknown_slot37(nick_index,unknown_string_83c55c,unknown_string_83c55c,1);
                    SendMessageA(nicknames,0x144,selected,0);
                }
                SendMessageA(nicknames,0x14e,-1,0);
            }
            Unknown_00739a50(window,1);InvalidateRect(nicknames,0,0);
            EnableWindow(GetDlgItem(window,0x6eb),0);SendMessageA(nicknames,0x14e,0,0);
            rc_ptr<PlayerProfile> profile=PlayerProfile::Load_Default();
            if(profile.Get()) {
                profile->Populate_Dialog_00739b70(window,unknown_string_83c55c,false);
                HWND automatic=GetDlgItem(window,0x6ff);
                SendMessageA(automatic,0x49d,0,1);EnableWindow(automatic,0);
                SendMessageA(automatic,0xf1,0,0);SendMessageA(automatic,0x49d,0,0);InvalidateRect(automatic,0,0);
            }
            return 0;
        }
        case 0x6ec: {
            char url[256];sprintf(url,profile_registration_url_7fd5a4,profile_url_value_b2ac5c);
            View_HTML_0073c580(url,0);return 0;
        }
        }
        break;
    case 0x4ed:ShowWindow(window,0);unknown_dialog_5ecf40(window,1);return 0;
    case 0x497: {
        HWND nicknames=GetDlgItem(window,0x628);
        unknown_reset_combo_6007f0(nicknames);SendMessageA(nicknames,0x141,9,0);
        WideString prompt(StringTable::Load_String(profile_choose_nick_7fd2f0,0,wol_source_file_007fd62c,0x5a2e));
        int item=SendMessageA(nicknames,0x4c2,0,(LPARAM)prompt.unknown_text_770430());
        SendMessageA(nicknames,0x151,item,-1);SendMessageA(nicknames,0x14e,item,0);
        char const *nickname,*password;
        for(int nick_index=1;nick_index<=32;++nick_index) {
            nickname=0;password=0;
            if(unknown_chat_a72cfc->unknown_slot36(nick_index,&nickname,&password)==0 && nickname) {
                if(strlen(nickname)>0) {
                    WideString wide=Wstring_To_Wide(nickname);
                    int entry=SendMessageA(nicknames,0x4c2,0,(LPARAM)wide.unknown_text_770430());
                    SendMessageA(nicknames,0x151,entry,nick_index);
                }
            }
        }
        Unknown_00753240(GetDlgItem(window,0x62a));
        Fill_Side_Combo_4d1560(window,0x6a1);Init_Color_Entries_4d1ea0();Fill_Color_Combo_4d2080(window,0x6a2);
        Populate_Server_Choices_007454c0(GetDlgItem(window,0x629),true);
        rc_ptr<PlayerProfile> profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
        if(profile.Get()) profile->Populate_Dialog_00739b70(window,unknown_wstring_b26cb8,true);
        int selected_nick=-1;int selected=SendMessageA(nicknames,0x147,0,0);
        if(selected!=-1) selected_nick=SendMessageA(nicknames,0x150,selected,0);
        BOOL valid=selected_nick!=-1;
        EnableWindow(GetDlgItem(window,0x6eb),valid);EnableWindow(GetDlgItem(window,0x687),valid);HWND automatic_button=GetDlgItem(window,0x6ff);EnableWindow(automatic_button,valid);
        Wstring automatic=WOL_Auto_Login_Persona();
        SendMessageA(GetDlgItem(window,0x6ff),0xf1,(automatic==unknown_wstring_b26cb8)?1:0,0);
    } break;
    }
    return 0;
}
