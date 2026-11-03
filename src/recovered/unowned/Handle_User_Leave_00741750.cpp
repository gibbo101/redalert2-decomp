// Updates WOL and lobby state after a user leaves a channel.
#define VECTOR_IMPLEMENT_ALL
#define RA2_WOL_USER_INLINE_SHRINK
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/win_util.hpp"
static inline HWND Get_Item(HWND window, int id) { return GetDlgItem(window,id); }
extern wchar_t wol_scenario_description_a3d342[];
extern int wol_player_pings_b292ac[8];
extern int wol_lan_leave_b2abf0;
extern char leave_debug_local_7fe45c[],leave_debug_started_7fe42c[],leave_debug_clear_7fe410[];
extern char leave_debug_lan_guest_7fe3f0[],leave_debug_lan_game_7fe3d0[],leave_debug_running_7fe39c[];
extern char lobby_prefix_7fd358[];
extern wchar_t lobby_name_format_7d9c94[];
extern wchar_t lobby_number_format_7fd91c[];
extern char leave_text_label_7fe420[],wol_source_path_7fd62c[];
HWND __fastcall Unknown_00735B10();
void __stdcall unknown_dialog_5ecf40(HWND window,int result);
void __fastcall Unknown_005cd030(HWND window,bool update);
void __fastcall Unknown_Release_Slot_by_Name_005c9270(char const *name);
bool __fastcall Unknown_005c9320(NodeNameType *entry);
void __fastcall Store_User_Ping_0075b110(char const *name,int ping);
void __fastcall Refresh_Game_List_0073f8f0();
void __fastcall Unknown_0073c480();
int __fastcall Join_Selected_Lobby_00744930(bool unknown);
void __fastcall Unknown_005C2C80(int color,wchar_t const *format,...);
void __fastcall Handle_User_Leave_00741750(WOL::User *user)
{
    _stricmp(unknown_wstring_b26cb8.Get(),user->name);
    if (unknown_channel_b299c0.unknown_00 != 0) Voc_Play(Rules->PlayerLeft,1.0f,0x2000,0);
    if (user->flags & 0x8000) {
        Debug_Printf(leave_debug_local_7fe45c);
        if (unknown_b2ac40 != 0) Debug_Printf(leave_debug_started_7fe42c);
        wchar_t name[64];
        Unknown_006FA0C0(name,unknown_channel_b299c0.name,-1);
        if (strncmp(unknown_channel_b299c0.name,lobby_prefix_7fd358,7) == 0) {
            int number = atol(unknown_channel_b299c0.name+strlen(lobby_prefix_7fd358));
            int page = number/8;
            int lobby = number%8;
            if (page == 0) swprintf(name,lobby_name_format_7d9c94,unknown_lobby_names_b26c94[lobby]);
            else swprintf(name,lobby_number_format_7fd91c,unknown_lobby_names_b26c94[lobby],page+1);
        }
        if (!Is_Online_Session())
            Unknown_005C2C80(unknown_color_7a7360,StringTable::Load_String(leave_text_label_7fe420,0,wol_source_path_7fd62c,0x1f39),name);
        unknown_b2abe8=0;
        Debug_Printf(leave_debug_clear_7fe410);
        memset(&unknown_channel_b299c0,0,sizeof(unknown_channel_b299c0));
        memset(unknown_player_b29cf0,0,sizeof(unknown_player_b29cf0));
        unknown_users_b2a728.Count=0;
        unknown_b2ac58=0;
        HWND wait=Find_Dialog_00735940(0xc4);
        if (wait) {
            unknown_b2abe0 &= ~0x40;
            if (unknown_b2abe0 == 0) End_Dialog_007357e0(wait,0);
        }
        HWND active=Unknown_00735B10();
        HWND focus=Get_Item(active,0x540);
        if (focus) SetFocus(focus);
        wol_scenario_description_a3d342[0]=0;
        ++unknown_counter_a3fabc;
        unknown_session_a3d298.ScenarioFileLength_87c=0;
        unknown_session_a3d298.ScenarioDigest_85a[0]=0;
        HWND main=Find_Dialog_00735940(0x113);
        if (main && unknown_b2abd9) {
            ShowWindow(main,0);
            unknown_dialog_5ecf40(main,1);
        }
        HWND guest=Find_Dialog_00735940(0xc9);
        if (guest) {
            End_Dialog_007357e0(guest,2);
            ShowWindow(guest,0);
            unknown_dialog_5ecf40(guest,1);
            if (unknown_a3d2a4 == 3) {
                if (unknown_b2abd9) {
                    if (main) {
                        ShowWindow(main,0);
                        unknown_dialog_5ecf40(main,1);
                    }
                } else {
                    Join_Selected_Lobby_00744930(false);
                    if (main) PostMessageA(main,0x593,0,0);
                }
            } else if (unknown_a3d2a4 == 4) {
                Debug_Printf(leave_debug_lan_guest_7fe3f0);
                wol_lan_leave_b2abf0=1;
            }
        }
        HWND game=Find_Dialog_00735940(0xc2);
        if (game) {
            End_Dialog_007357e0(game,2);
            ShowWindow(game,0);
            unknown_dialog_5ecf40(game,1);
            if (unknown_a3d2a4 == 3) {
                if (unknown_b2abd9) {
                    if (main) {
                        ShowWindow(main,0);
                        unknown_dialog_5ecf40(main,1);
                    }
                } else {
                    Join_Selected_Lobby_00744930(false);
                    if (main) PostMessageA(main,0x593,0,0);
                }
            } else if (unknown_a3d2a4 == 4) Debug_Printf(leave_debug_lan_game_7fe3d0);
        }
        if (main) {
            if (!unknown_b2abd9) {
                ShowWindow(main,5);
                unknown_dialog_5ecf40(main,0);
            }
            Refresh_Game_List_0073f8f0();
        }
        --unknown_counter_a3fabc;
        return;
    }
    if (unknown_b2ac40 == 2) {
        Debug_Printf(leave_debug_running_7fe39c);
        return;
    }
    if (user) {
        for (int slot=0;slot<8;++slot) {
            if (unknown_player_slots_a3fa98[slot] && !strcmp(Unknown_006FA120(unknown_player_slots_a3fa98[slot]->Name),user->name)) {
                HWND lobby=Find_Lobby_Window_005c2c40();
                if (lobby) Set_Player_Ping_4d1060(lobby,slot,-1);
                break;
            }
        }
    }
    WOL::User other;
    for (int index=0;index<unknown_users_b2a728.Count;++index) {
        unknown_users_b2a728.Get_Copy(other,index);
        if (!_stricmp(other.name,user->name)) {
            unknown_users_b2a728.Remove(index);
            if (unknown_channel_b299c0.unknown_00 != 0) {
                memmove(unknown_player_b29cf0+index,unknown_player_b29cf0+index+1,sizeof(WolPlayerData)*(15-index));
                if (unknown_b2ac40 != 2) {
                    unsigned accepted_end=(unsigned)(unknown_player_b29cf0+16)+0x20;
                    for (unsigned accepted=(unsigned)&unknown_player_b29cf0[1].unknown_20; accepted<accepted_end; accepted+=sizeof(WolPlayerData)) {
                        *(int *)accepted=0;
                        EnableWindow(GetDlgItem(Find_Lobby_Window_005c2c40(),0x59f),1);
                    }
                    if (!unknown_b2ac58) {
                        HWND dialog=Find_Dialog_00735940(0xc9);
                        Unknown_005cd030(dialog,true);
                    }
                    Unknown_005c9700();
                }
            }
            if (index == 0 && unknown_channel_b299c0.unknown_00 != 0 && !unknown_b2ac58)
                unknown_chat_a72cfc->unknown_slot09();
            break;
        }
    }
    if (unknown_channel_b299c0.unknown_00 != 0) {
        Unknown_Release_Slot_by_Name_005c9270(user->name);
        for (int player=0;player<unknown_players_a3fa7c.Count();++player) {
            if (!_stricmp(Unknown_006FA120(unknown_players_a3fa7c[player]->Name),user->name)) {
                NodeNameType *entry=unknown_players_a3fa7c[player];
                unknown_players_a3fa7c.Delete(player);
                unknown_session_a3d298.Unknown_00672F20(player);
                delete entry;
                break;
            }
        }
        for (int slot=0;slot<8;++slot) {
            if (!unknown_player_slots_a3fa98[slot] || !Unknown_005c9320(unknown_player_slots_a3fa98[slot])) wol_player_pings_b292ac[slot]=-1;
            char *name=Unknown_006FA120(unknown_player_slots_a3fa98[slot]->Name);
            Store_User_Ping_0075b110(name,wol_player_pings_b292ac[slot]);
        }
        if (unknown_b2ac58) {
            Unknown_005c9700();
            Unknown_0073c480();
            Unknown_005c3810(true,true);
            if (Current_Dialog_Id_00735b20() == 0x6b) {
                HWND window=Unknown_00735B10();
                int index=SendDlgItemMessageA(window,0x6eb,0x188,0,0);
                if (index != -1) {
                    UnknownSessionA3D29C *mode=(UnknownSessionA3D29C *)SendDlgItemMessageA(window,0x6eb,0x199,index,0);
                    if (mode) {
                        mode->unknown_slot30();
                        Unknown_0073FEE0(0,false);
                        return;
                    }
                }
            } else if (unknown_session_a3d29c) unknown_session_a3d29c->unknown_slot30();
        }
    }
    Unknown_0073FEE0(0,false);
}
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Current_Dialog_Id_00735b20@@YAHXZ=00735b20
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?End_Dialog_007357e0@@YI_NPAUHWND__@@H@Z=007357e0
// @ref ?Find_Dialog_00735940@@YIPAUHWND__@@H@Z=00735940
// @ref ?Find_Lobby_Window_005c2c40@@YAPAUHWND__@@XZ=005c2c40
// @ref ?Get@Wstring@@QBEPBDXZ=0076e6f0
// @ref ?Join_Selected_Lobby_00744930@@YIH_N@Z=00744930
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Refresh_Game_List_0073f8f0@@YIXXZ=0073f8f0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Set_Player_Ping_4d1060@@YIXPAUHWND__@@HH@Z=004d1060
// @ref ?Store_User_Ping_0075b110@@YIXPBDH@Z=0075b110
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80
// @ref ?Unknown_005c3810@@YIX_N0@Z=005c3810
// @ref ?Unknown_005c9320@@YI_NPAUNodeNameType@@@Z=005c9320
// @ref ?Unknown_005c9700@@YAXXZ=005c9700
// @ref ?Unknown_005cd030@@YIXPAUHWND__@@_N@Z=005cd030
// @ref ?Unknown_00672F20@UnknownSessionState@@QAEXH@Z=00672f20
// @ref ?Unknown_006FA0C0@@YIXPAGPBDH@Z=006fa0c0
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref ?Unknown_00735B10@@YIPAUHWND__@@XZ=00735b10
// @ref ?Unknown_0073FEE0@@YIXH_N@Z=0073fee0
// @ref ?Unknown_0073c480@@YIXXZ=0073c480
// @ref ?Unknown_Release_Slot_by_Name_005c9270@@YIXPBD@Z=005c9270
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?leave_debug_clear_7fe410@@3PADA=007fe410
// @ref ?leave_debug_lan_game_7fe3d0@@3PADA=007fe3d0
// @ref ?leave_debug_lan_guest_7fe3f0@@3PADA=007fe3f0
// @ref ?leave_debug_local_7fe45c@@3PADA=007fe45c
// @ref ?leave_debug_running_7fe39c@@3PADA=007fe39c
// @ref ?leave_debug_started_7fe42c@@3PADA=007fe42c
// @ref ?leave_text_label_7fe420@@3PADA=007fe420
// @ref ?lobby_name_format_7d9c94@@3PAGA=007d9c94
// @ref ?lobby_number_format_7fd91c@@3PAGA=007fd91c
// @ref ?lobby_prefix_7fd358@@3PADA=007fd358
// @ref ?unknown_a3d2a4@@3HA=00a3d2a4
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref ?unknown_b2abe0@@3IA=00b2abe0
// @ref ?unknown_b2abe8@@3HA=00b2abe8
// @ref ?unknown_b2ac40@@3HA=00b2ac40
// @ref ?unknown_b2ac58@@3HA=00b2ac58
// @ref ?unknown_channel_b299c0@@3UChannel@WOL@@A=00b299c0
// @ref ?unknown_chat_a72cfc@@3PAUIChat@WOL@@A=00a72cfc
// @ref ?unknown_color_7a7360@@3HA=007a7360
// @ref ?unknown_counter_a3fabc@@3HA=00a3fabc
// @ref ?unknown_dialog_5ecf40@@YGXPAUHWND__@@H@Z=005ecf40
// @ref ?unknown_lobby_names_b26c94@@3PAPADA=00b26c94
// @ref ?unknown_player_b29cf0@@3PAUWolPlayerData@@A=00b29cf0
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_session_a3d29c@@3PAVUnknownSessionA3D29C@@A=00a3d29c
// @ref ?unknown_users_b2a728@@3VWolUserArray@@A=00b2a728
// @ref ?unknown_wstring_b26cb8@@3VWstring@@A=00b26cb8
// @ref ?wol_lan_leave_b2abf0@@3HA=00b2abf0
// @ref ?wol_player_pings_b292ac@@3PAHA=00b292ac
// @ref ?wol_scenario_description_a3d342@@3PAGA=00a3d342
// @ref ?wol_source_path_7fd62c@@3PADA=007fd62c
// @ref __imp__EnableWindow@8=0079a490
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__PostMessageA@16=0079a470
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref __imp__SetFocus@4=0079a38c
// @ref __imp__ShowWindow@8=0079a498
// @ref __stricmp=00781f20
// @ref _atol=00782d72
// @ref _memmove=00783290
// @ref _strncmp=00783810
// @ref _swprintf=00783764
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
