// int __stdcall Wonline_Options_Dialog_00749b50(HWND,UINT,WPARAM,LPARAM) (0x00749B50): the WOL options dialog. Twin: TibSun WOL_Options_Dialog_Proc; original 970 B + 6 NOP.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/wol_settings.hpp"
#include "shared/sound_controls.hpp"
#include "shared/win_util.hpp"
#include "shared/theme.hpp"
extern int wol_pending_allow_page_b292e4,wol_pending_allow_find_b294f0,wol_pending_lang_filter_b29810,wol_pending_lob_music_b297cc;
extern int wol_pending_show_all_b2a644,wol_pending_display_asian_b29730,wol_pending_display_latin_b29978;
extern void *unknown_options_b2aca0;
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
void __fastcall unknown_5159b0(int,bool);
void __stdcall unknown_dialog_5ecf40(HWND,int);
// @ref ?unknown_options_b2aca0@@3PAXA=00b2aca0
int __stdcall Wonline_Options_Dialog_00749b50(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    long result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(result) return result;
    switch(message) {
    case 2:
        unknown_flag_a40958=true;
        return 0;
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
        return 0;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x111:
        switch((int)(wparam&0xffff)) {
        case 1: {
            wol_pending_allow_page_b292e4=0;
            HWND item=GetDlgItem(window,0x5f5);
            if(item) wol_pending_allow_page_b292e4=SendMessageA(item,0xf0,0,0);
            wol_pending_allow_find_b294f0=0;
            item=GetDlgItem(window,0x5f7);
            if(item) wol_pending_allow_find_b294f0=SendMessageA(item,0xf0,0,0);
            wol_pending_lang_filter_b29810=0;
            item=GetDlgItem(window,0x5f6);
            if(item) wol_pending_lang_filter_b29810=SendMessageA(item,0xf0,0,0);
            wol_pending_lob_music_b297cc=0;
            item=GetDlgItem(window,0x5f8);
            if(item) wol_pending_lob_music_b297cc=SendMessageA(item,0xf0,0,0);
            item=GetDlgItem(window,0x5f9);
            if(item) wol_pending_show_all_b2a644=SendMessageA(item,0xf0,0,0);
            wol_pending_display_asian_b29730=0;
            item=GetDlgItem(window,0x5fa);
            if(item) wol_pending_display_asian_b29730=SendMessageA(item,0xf0,0,0);
            wol_pending_display_latin_b29978=0;
            item=GetDlgItem(window,0x5fb);
            if(item) wol_pending_display_latin_b29978=SendMessageA(item,0xf0,0,0);
            operator delete(unknown_options_b2aca0);
            unknown_options_b2aca0=0;
            End_Dialog_007357e0(window,1);
            return 0;
        }
        case 2:
            operator delete(unknown_options_b2aca0);
            unknown_options_b2aca0=0;
            End_Dialog_007357e0(window,2);
            return 0;
        case 0x5f8:
            if((short)(wparam>>16)==1||(short)(wparam>>16)==0) {
                bool checked=SendMessageA((HWND)lparam,0xf0,0,0)==1;
                if(checked && !Theme.Still_Playing()) Restart_Lobby_Music();
                else if(checked) { if(Theme.What_Is_Playing()==Theme.From_Name("INTRO")) Restart_Lobby_Music(); }
                else if(!checked) Theme.Queue_Song(-3);
                break;
            }
            break;
        case 0x63a: {
            OwnerDraw::unknown_5e5150(window,false);
            unknown_5159b0(0,true);
            unknown_flag_a40958=false;
            SoundControlsDialog dialog;
            dialog.Run_00688CD0();
            ShowWindow(window,5);
            unknown_dialog_5ecf40(window,0);
            return 0;
        }
        }
        break;
    case 0x497:
        if(unknown_wol_allow_page_b290a0) SendDlgItemMessageA(window,0x5f5,0xf1,1,0);
        if(unknown_wol_allow_find_b2a818) SendDlgItemMessageA(window,0x5f7,0xf1,1,0);
        if(unknown_wol_lang_filter_b2a7e4) SendDlgItemMessageA(window,0x5f6,0xf1,1,0);
        if(unknown_wol_lob_music_b297c8) SendDlgItemMessageA(window,0x5f8,0xf1,1,0);
        if(unknown_wol_show_all_b2a634) SendDlgItemMessageA(window,0x5f9,0xf1,1,0);
        if(unknown_wol_display_asian_b2a804) SendDlgItemMessageA(window,0x5fa,0xf1,1,0);
        if(unknown_wol_display_latin_b2a7e8) SendDlgItemMessageA(window,0x5fb,0xf1,1,0);
        break;
    case 0x4ed:
        ShowWindow(window,0);
        unknown_dialog_5ecf40(window,1);
        return 0;
    }
    return 0;
}
