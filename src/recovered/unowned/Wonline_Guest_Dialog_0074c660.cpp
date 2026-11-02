#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/session_state.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/options_dialog.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/progress_screen.hpp"
#include "shared/map_preview.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/crt_string.hpp"
namespace OwnerDraw {
WideString __fastcall unknown_5e2160(HWND,int);
WideString __fastcall unknown_5e2260(unsigned int,HWND);
}
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
void __stdcall unknown_dialog_5ecf40(HWND,int);
void __fastcall Refresh_Wonline_Players_0073fee0(int,bool);
wchar_t *__fastcall Player_Info_Tooltip_0074a120(wchar_t const *);
wchar_t *__fastcall Unknown_0074a4e0(wchar_t const *);
int __fastcall Unknown_0073cb80(WideString const &);
int __fastcall Unknown_0073ca50(WideString const &);
int __fastcall Parse_Page_Command_00746480(wchar_t const *);
int __fastcall Reply_To_Last_Pager_007466c0(wchar_t const *);
int __fastcall Parse_Online_Command_00746240(wchar_t const *);
extern "C" wchar_t *__cdecl wcsncpy(wchar_t *,wchar_t const *,unsigned);
extern "C" int __cdecl wcsncmp(wchar_t const *,wchar_t const *,unsigned);
extern wchar_t guest_empty_wide_839d4c[];
extern char guest_last_pager_b2ac48[];
extern int guest_action_color_7a7370,guest_private_action_color_7a736c;
extern int guest_chat_color_7a737c,guest_private_color_7a7368;
// @ref ?unknown_5e2160@OwnerDraw@@YI?AVWideString@@PAUHWND__@@H@Z=005e2160
// @ref ?unknown_5e2260@OwnerDraw@@YI?AVWideString@@IPAUHWND__@@@Z=005e2260
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?unknown_dialog_5ecf40@@YGXPAUHWND__@@H@Z=005ecf40
// @ref ?Refresh_Wonline_Players_0073fee0@@YIXH_N@Z=0073fee0
// @ref ?Player_Info_Tooltip_0074a120@@YIPAGPBG@Z=0074a120
// @ref ?Parse_Page_Command_00746480@@YIHPBG@Z=00746480
// @ref ?Reply_To_Last_Pager_007466c0@@YIHPBG@Z=007466c0
// @ref ?guest_empty_wide_839d4c@@3PAGA=00839d4c
// @ref ?guest_last_pager_b2ac48@@3PADA=00b2ac48
// @ref ?guest_action_color_7a7370@@3HA=007a7370
// @ref ?guest_private_action_color_7a736c@@3HA=007a736c
// @ref ?guest_chat_color_7a737c@@3HA=007a737c
// @ref ?guest_private_color_7a7368@@3HA=007a7368
// @ref _wcsncpy=00783622
// @ref _wcsncmp=007846cc
extern char guest_label_7fe9fc[];
// @ref ?guest_label_7fe9fc@@3PADA=007fe9fc
extern char guest_label_7fe9e8[];
// @ref ?guest_label_7fe9e8@@3PADA=007fe9e8
extern wchar_t guest_label_7fe2c4[];
// @ref ?guest_label_7fe2c4@@3PAGA=007fe2c4
extern char guest_label_7e6d74[];
// @ref ?guest_label_7e6d74@@3PADA=007e6d74
extern char guest_label_7dfc7c[];
// @ref ?guest_label_7dfc7c@@3PADA=007dfc7c
extern wchar_t guest_label_7d64f4[];
// @ref ?guest_label_7d64f4@@3PAGA=007d64f4
extern char guest_label_7fe9d4[];
// @ref ?guest_label_7fe9d4@@3PADA=007fe9d4
extern char guest_label_7dfc64[];
// @ref ?guest_label_7dfc64@@3PADA=007dfc64
extern wchar_t guest_label_7fe9b8[];
// @ref ?guest_label_7fe9b8@@3PAGA=007fe9b8
extern char guest_label_7dfc48[];
// @ref ?guest_label_7dfc48@@3PADA=007dfc48
extern char guest_label_7dfc14[];
// @ref ?guest_label_7dfc14@@3PADA=007dfc14
extern char guest_label_7dfbfc[];
// @ref ?guest_label_7dfbfc@@3PADA=007dfbfc
extern wchar_t guest_label_7fe9a4[];
// @ref ?guest_label_7fe9a4@@3PAGA=007fe9a4
extern char guest_label_7fec94[];
// @ref ?guest_label_7fec94@@3PADA=007fec94
extern char guest_label_7fec84[];
// @ref ?guest_label_7fec84@@3PADA=007fec84
extern char guest_label_7fdea0[];
// @ref ?guest_label_7fdea0@@3PADA=007fdea0
extern char guest_label_7e8fe8[];
// @ref ?guest_label_7e8fe8@@3PADA=007e8fe8
extern char guest_label_7e8e28[];
// @ref ?guest_label_7e8e28@@3PADA=007e8e28
extern char guest_label_7eb2e4[];
// @ref ?guest_label_7eb2e4@@3PADA=007eb2e4
extern char guest_label_7eb2d8[];
// @ref ?guest_label_7eb2d8@@3PADA=007eb2d8
extern char wol_source_file_007fd62c[];
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
int __stdcall Wonline_Guest_Dialog_0074c660(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    int handled=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(handled) return handled;
    switch(message) {
    case 0x84: {
        HWND tooltip=GetDlgItem(window,0x695);
        if(!tooltip) return 0;
        POINT point;
        point.x=lparam&0xffff;
        point.y=(unsigned)lparam>>16;
        RECT bounds;
        GetWindowRect(window,&bounds);
        point.x-=bounds.left;
        point.y-=bounds.top;
        WideString text;
        HWND child=ChildWindowFromPointEx(window,point,1);
        if(child) {
            text=OwnerDraw::unknown_5e2160(window,(int)child);
            if(Compare_Wide_007837d3(text.Get(),guest_empty_wide_839d4c)==0)
                text=OwnerDraw::unknown_5e2260((unsigned)window,child);
        }
        SendMessageA(tooltip,0x4b2,0,(LPARAM)text.unknown_text_770430());
        return 0;
    }
    case 2:
        if(ProgressScreen.Has_Window()) ProgressScreen.Clear_Window();
        if(unknown_dialog_preview_a72ce8) {
            delete unknown_dialog_preview_a72ce8;
            unknown_dialog_preview_a72ce8=0;
        }
        return 0;
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        if(unknown_dialog_preview_a72ce8) unknown_dialog_preview_a72ce8->Draw_0061D460(window);
        if(ProgressScreen.Has_Window()) ProgressScreen.Draw_It(Point2D(-1,-1));
        ValidateRect(window,0);
        return 0;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x111: {
        int command=wparam&0xffff;
        switch(command) {
        case 2:
            if(!unknown_b2ac40 && unknown_chat_a72cfc->unknown_slot09()<0) Unknown_007357E0(window,2);
            return 0;
        case 0x3ed: {
            HWND input=GetDlgItem(window,0x540);
            WideString text=Limit_Name_Text_005ccf50(input);
            SendMessageA(input,0x4b2,0,(LPARAM)guest_empty_wide_839d4c);
            SetFocus(input);
            InvalidateRect(input,0,0);
            int color=guest_action_color_7a7370;
            if(strlen(unknown_channel_b299c0.name)==0)
                Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7fe9fc,0,wol_source_file_007fd62c,0x3dae));
            else if(text.Length()>0) {
                if(Unknown_0073cb80(text)) color=guest_private_action_color_7a736c;
                Unknown_005C2C80(color,guest_label_7fe2c4,unknown_wstring_b26cb8.Buffer,text.Get());
            } else Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7fe9e8,0,wol_source_file_007fd62c,0x3db6));
            return 0;
        }
        case 0x59f: {
            unknown_players_a3fa7c[0]->unknown_67=1;
            char options[64];
            sprintf(options,guest_label_7e6d74);
            Send_Game_Options_005c3c60(options);
            Unknown_005cd030(window,false);
            HWND accept=GetDlgItem(window,0x59f);
            EnableWindow(accept,0);
            InvalidateRect(accept,0,0);
            SendMessageA(accept,0x4dc,0,0);
            Refresh_Wonline_Players_0073fee0(0,false);
            SetFocus(GetDlgItem(window,0x540));
            return 0;
        }
        case 0x540: {
            wchar_t nickname[16],primary_command[64],alternate_command[64];
            WideString text=Limit_Name_Text_005ccf50((HWND)lparam);
            if((unsigned short)(wparam>>16)==0x501) {
                SendMessageA((HWND)lparam,0x4b2,0,(LPARAM)guest_empty_wide_839d4c);
                if(text.Length()>0) {
                    int parsed=Parse_Page_Command_00746480(text.Get());
                    if(parsed!=0) {
                        if(parsed==1) {
                            int count=0;
                            unsigned length=text.Length()+1;
                            wchar_t *copy=(wchar_t *)operator new(length*2);
                            wcscpy(primary_command,StringTable::Load_String(guest_label_7dfc7c,0,wol_source_file_007fd62c,0x3d3b));
                            if(!copy) return 0;
                            copy=wcsncpy(copy,text.Get(),length);
                            if(!copy) return 0;
                            wchar_t *body=copy+wcslen(primary_command);
                            while(*body && wcsncmp(body,guest_label_7d64f4,1)==0) ++body;
                            while(*body) {
                                if(wcsncmp(body,guest_label_7d64f4,1)==0 || count>10) break;
                                nickname[count++]=*body++;
                            }
                            nickname[count]=0;
                            while(*body && wcsncmp(body,guest_label_7d64f4,1)==0) ++body;
                            if(count>10) Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7fe9d4,0,wol_source_file_007fd62c,0x3d59));
                            else if(count==0) Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7dfc64,0,wol_source_file_007fd62c,0x3d5b));
                            else if(wcslen(body)>0) Unknown_005C2C80(guest_private_color_7a7368,guest_label_7fe9b8,unknown_wstring_b26cb8.Buffer,nickname,body);
                            else Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7dfc48,0,wol_source_file_007fd62c,0x3d61));
                            operator delete(copy);
                        }
                    } else if(Reply_To_Last_Pager_007466c0(text.Get())) {
                        unsigned length=text.Length()+1;
                        wchar_t *copy=(wchar_t *)operator new(length*2);
                        wcscpy(primary_command,StringTable::Load_String(guest_label_7dfc14,0,wol_source_file_007fd62c,0x3d73));
                        wcscpy(alternate_command,StringTable::Load_String(guest_label_7dfbfc,0,wol_source_file_007fd62c,0x3d74));
                        if(!copy) return 0;
                        copy=wcsncpy(copy,text.Get(),length);
                        if(!copy) return 0;
                        wchar_t *body=copy+(wcsncmp(copy,primary_command,wcslen(primary_command))==0 ? wcslen(primary_command):wcslen(alternate_command));
                        while(*body && wcsncmp(body,guest_label_7d64f4,1)==0) ++body;
                        wcscpy(nickname,Unknown_006FA180(guest_last_pager_b2ac48));
                        if(wcslen(nickname)>0 && wcslen(body)>0)
                            Unknown_005C2C80(guest_private_color_7a7368,guest_label_7fe9b8,unknown_wstring_b26cb8.Buffer,nickname,body);
                        else if(wcslen(nickname)>0)
                            Unknown_005C2C80(-1,StringTable::Load_String(guest_label_7dfc48,0,wol_source_file_007fd62c,0x3d91));
                        operator delete(copy);
                    } else if(!Parse_Online_Command_00746240(text.Get())) {
                        int color=guest_chat_color_7a737c;
                        if(Unknown_0073ca50(text)==1) color=guest_private_color_7a7368;
                        Unknown_005C2C80(color,guest_label_7fe9a4,unknown_wstring_b26cb8.Buffer,text.Get());
                    }
                }
            }
            return 0;
        }
        case 0x510: case 0x513: case 0x514:
        case 0x51e: case 0x51f: case 0x520: case 0x521: case 0x522: case 0x523:
        case 0x524: case 0x525: case 0x526: case 0x527: case 0x528:
        case 0x6a1: case 0x6a2:
            if((unsigned short)(wparam>>16)!=1) return 0;
        case 0x7fff: {
            Debug_Printf(guest_label_7fec94);
            int side_player=Side_Combo_Player_4d13b0(command);
            int color_player=Color_Combo_Player_4d1d10(command);
            int player=side_player>color_player?side_player:color_player;
            int side=Player_Side_Combo_ID_4d1350(player);
            int color=Player_Color_Combo_ID_4d1cb0(player);
            if(player==side_player) Set_Slot_Country_005c9a10(window,side);
            else Set_Slot_Color_005c9ab0(window,color);
            int requested_side=Side_Combo_Data_4d1c70(window,side,-1);
            int requested_color=Color_Combo_Data_4d2900(window,color,-1);
            unsigned char network[4],node[6];
            unsigned short socket;
            unknown_address_a3fbc8.Get_Address(network,node,&socket);
            char options[128];
            sprintf(options,guest_label_7fec84,requested_side,requested_color,*(unsigned int *)node,unknown_firewall_a71b18.unknown_00&0xffff,unknown_a40230);
            Debug_Printf(guest_label_7fdea0,options);
            Wstring host=Narrow_Copy_00771280(unknown_host_name_a3f618);
            Unknown_005c3d90(host.Get(),options);
            return 0;
        }
        }
        return 0;
    }
    case 0x497: {
        SetFocus(GetDlgItem(window,0x540));
        SendDlgItemMessageA(window,0x3ed,0x49c,0,(LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(guest_label_7eb2e4,0));
        SendDlgItemMessageA(window,0x3ed,0x4aa,0,(LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(guest_label_7eb2d8,0));
        MultiplayerGameMode *mode=MultiplayerGameMode::unknown_first_mode_5b6ec0();
        unknown_session_a3d298.GameModeIndex=mode->unknown_28;
        Unknown_005c3450(window,mode);
        unknown_session_a3d2b4=mode->unknown_slot13();
        Select_Scenario_005c7c30(unknown_session_a3d2b4);
        Fill_Side_Combos_4d16d0(window);
        Init_Color_Entries_4d1ea0();
        Fill_Color_Combos_4d2300(window);
        Select_Scenario_005c7c30(-1);
        unknown_a72d52=false;
        unknown_int_a3db1c=8;
        Unknown_005c34b0(window);
        Unknown_005c7570(window);
        Unknown_Fill_Options_Dialog_005c3550(window,1);
        Refresh_Wonline_Players_0073fee0(0,false);
        return 0;
    }
    case 0x4e9: {
        OwnerDraw::UnknownTextRequest *request=(OwnerDraw::UnknownTextRequest *)lparam;
        int id;
        {
            WideString &text=request->text;
            text=(wchar_t const *)0;
            if(!request->unknown_00) goto tooltip_done;
            id=GetDlgCtrlID((HWND)request->unknown_00);
            if(request->unknown_04!=-1) {
                if(Control_Slot_005c9800(id)==-1) {
                    if(Side_Combo_Player_4d13b0(id)==-1) {
                        if(Color_Combo_Player_4d1d10(id)!=-1) {
                            text=Color_Name_4d1d80(Color_Combo_Data_4d2900(window,id,request->unknown_04));
                            return 1;
                        }
                    } else {
                        int country=Side_Combo_Data_4d1c70(window,id,request->unknown_04);
                        if(country!=-1) { text=Side_Name_4d1420(country); return 1; }
                    }
                } else {
                    NodeNameType *entry=(NodeNameType *)unknown_combo_selected_data_005c99d0(window,id,request->unknown_04);
                    text=Entry_Type_Name_005c9870(entry);
                    return 1;
                }
                goto tooltip_done;
            }
            if(Control_Slot_005c9800(id)!=-1) {
                NodeNameType *entry=(NodeNameType *)unknown_combo_selected_data_005c99d0(window,id,-1);
                if(entry) {
                    WideString label=OwnerDraw::unknown_5e2260((unsigned)window,(HWND)request->unknown_00);
                    if((Compare_Wide_007837d3(label.Get(),StringTable::Load_String(guest_label_7e8fe8,0,wol_source_file_007fd62c,0x3c92))==0 ||
                        Compare_Wide_007837d3(label.Get(),StringTable::Load_String(guest_label_7e8e28,0,wol_source_file_007fd62c,0x3c92))==0) && Unknown_005c9320(entry))
                        label=Player_Info_Tooltip_0074a120(entry->Name);
                    text=label.Get();
                }
            }
        }
        {
            int player;
            if(id==0x754) player=0;
            else if(id==0x755) player=1;
            else if(id==0x756) player=2;
            else if(id==0x757) player=3;
            else if(id==0x758) player=4;
            else if(id==0x759) player=5;
            else if(id==0x75a) player=6;
            else if(id==0x75b) player=7;
            else goto tooltip_done;
            WideString ping;
            int slot=Slot_Control_Id_005c97a0(player);
            if(slot!=-1) {
                NodeNameType *entry=(NodeNameType *)unknown_combo_selected_data_005c99d0(window,slot,-1);
                if(entry && Unknown_005c9320(entry)) {
                    ping=Unknown_0074a4e0(entry->Name);
                    request->text=ping;
                }
            }
        }
tooltip_done:
        return 1;
    }
    case 0x4ed:
        ShowWindow(window,0);
        unknown_dialog_5ecf40(window,1);
        return 0;
    }
    return 0;
}
