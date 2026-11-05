// bool __fastcall Host_Game_007459a0() (0x007459A0)
// Hosts a WOL game: asks for the game's options (the quick match kinds skip the dialog), creates the game channel,
// rebuilds the session with the local player as host and opens the game setup dialog. Twin: TibSun wonline.cpp's
// IDC_NEWGAME case of WOL_Main_Dialog_Proc. Original 2,203 B + 5 NOP.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/create_game_dialog_control.hpp"
#include "shared/dialog_create.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
extern "C" int __cdecl sprintf(char *,char const *,...);
extern int wol_max_players_b2abdc;
void __fastcall Format_User_Options_0073cff0(char *);
int __fastcall Run_Control_Dialog_006011a0(int,DLGPROC,OwnerDraw::DialogControl *);
long __stdcall Wonline_Create_Game_Dialog_00748e10(HWND,UINT,WPARAM,LPARAM);
int __stdcall WOL_Game_Options_Proc_0074a710(HWND,UINT,WPARAM,LPARAM);
namespace seed_005c8cd0 { void __fastcall FUN_005c8cd0(int); }
void __fastcall unknown_5159b0(int,bool);
extern char wol_password_find_7e613c[],wol_password_replace_7cf730[],wol_game_name_format_7fe938[];
extern char wol_leave_debug_7fe6f8[],wol_leaving_label_7fe6e4[];
extern char wol_source_file_007fd62c[],wol_bad_key_label_7fe928[],wol_cant_create_label_7fe914[],wol_creating_label_7fe900[];
// @ref ??_7CreateGameDialogControl@@6B@=007af94c
// @ref ?Close_Wonline_Wait@@YIXI@Z=0074d780
// @ref ?wol_bad_key_label_7fe928@@3PADA=007fe928
// @ref ?wol_cant_create_label_7fe914@@3PADA=007fe914
// @ref ?wol_creating_label_7fe900@@3PADA=007fe900
// @ref ?wol_game_name_format_7fe938@@3PADA=007fe938
// Leave_Current_Channel 0x00744610 without its result, one inline level above the wait window close (depth 2 here).
inline void Leave_Game_Channel(unsigned int flags,bool show)
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
        Close_Wonline_Wait(0x40);
    }
}
// The text of a label of this file (name hypothesis).
inline wchar_t const *Wonline_Text(char *label,int line)
{
    return StringTable::Load_String(label,0,wol_source_file_007fd62c,line);
}
inline void Show_Game_Options()
{
    if(!Is_Online_Session()) {
        HWND window=Unknown_00735B10();
        if(window) {
            OwnerDraw::unknown_5e5150(window,false);
            unknown_5159b0(0,true);
        }
        unknown_5159b0(0,true);
        HWND dialog=unknown_create_dialog_5ff610(0xc2,(DialogProc)WOL_Game_Options_Proc_0074a710,0);
        unknown_session_a3d298.Mode->unknown_slot33();
        unknown_session_a3d298.Mode->unknown_slot8();
        unknown_session_a3d298.Mode->unknown_slot6();
        unknown_session_a3d298.Mode->unknown_slot26();
        ShowWindow(dialog,1);
        if(window) ShowWindow(window,0);
    }
}
inline void Reset_Session_Players()
{
    MultiplayerGameMode *mode=MultiplayerGameMode::unknown_first_mode_5b6ec0();
    unknown_session_a3d298.Mode=mode;
    unknown_session_a3d298.GameModeIndex=mode->unknown_28;
    mode->unknown_slot8();
    Select_Scenario_005c7c30(0);
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
    Clear_Slot_Lists_005c8a70();
    Unknown_Reset_Slots_005c8a90();
}
bool __fastcall Host_Game_007459a0()
{
    Wstring password;
    if(unknown_8523e0>=0x400) unknown_session_a3d298.WOLLimitResolution=false;
    CreateGameDialogControl control(unknown_session_a3d298.WOLLimitResolution,unknown_a72c68==1);
    unknown_b2ac04=false;
    if(Is_Online_Session()) wol_max_players_b2abdc=2;
    else {
        unknown_5159b0(0,true);
        if(Run_Control_Dialog_006011a0(0xc3,(DLGPROC)Wonline_Create_Game_Dialog_00748e10,&control)==2) return false;
        password=control.Text;
        password.Replace(wol_password_find_7e613c,wol_password_replace_7cf730);
    }
    unknown_chat_a72cfc->unknown_slot09();
    WOL::Channel channel;
    memset(&channel,0,sizeof(channel));
    sprintf(channel.channel_name,wol_game_name_format_7fe938,unknown_wstring_b26cb8);
    channel.unknown_00=0x21;
    channel.minUsers=1;
    if(wol_max_players_b2abdc<2) wol_max_players_b2abdc=4;
    strcpy(channel.key,password.Get());
    channel.maxUsers=wol_max_players_b2abdc;
    char user_options[80];
    memset(user_options,0,sizeof(user_options));
    Format_User_Options_0073cff0(user_options);
    user_options[40]=0;
    strcpy(channel.exInfo,user_options);
    if(unknown_session_a3d298.Type==4&&unknown_a3d2a4==2) {
        channel.unknown_14=1;
        channel.unknown_20|=0x1000;
    }
    else if(Is_Online_Session()) {
        channel.unknown_14=1;
        channel.unknown_20|=0x800;
    }
    else {
        channel.unknown_14=control.unknown_10;
        if(control.unknown_11) channel.unknown_20|=0x100;
        unknown_session_a3d298.WOLLimitResolution=control.unknown_12;
        if(control.unknown_12) channel.unknown_20|=unknown_8523e0==800?0x400:0x200;
    }
    channel.unknown_20+=unknown_b2abec;
    Leave_Game_Channel(0xc0,false);
    Reset_Session_Players();
    NodeNameType *who=new NodeNameType;
    memset(who,0,sizeof(NodeNameType));
    WideString name=Wstring_To_Wide(unknown_wstring_b26cb8);
    wcscpy(who->Name,name.Get());
    WolRegistryOptions options;
    options.Read_004ff200();
    rc_ptr<PlayerProfile> profile;
    if(options.unknown_004ff2c0()) profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
    else profile.Set(unknown_profile_b28cc4);
    if(profile.Get()) {
        unknown_session_a3d298.Set_Value_00672a30(profile->Country,false);
        unknown_session_a3d298.Set_Value_00672ae0(profile->Color,false);
    }
    who->unknown_66e2d0(unknown_session_a3d298.Value_0124_006729f0());
    who->unknown_66e300(unknown_session_a3d298.Value_011c_00672a10());
    who->unknown_67=1;
    who->Team=0;
    unknown_lobby_flag_7e6d90=7;
    unknown_a72c68=control.unknown_13;
    Unknown_005cd540(0);
    if(unknown_a72c68) {
        unknown_lobby_flag_7e6d90=0;
        who->Team=-1;
        who->unknown_66e2d0(-3);
    }
    unknown_players_a3fa7c.Add(who);
    seed_005c8cd0::FUN_005c8cd0(0);
    wcscpy(unknown_host_name_a3f618,name.Get());
    HRESULT result=unknown_chat_a72cfc->unknown_slot07(&channel);
    if(result==0x800401f8) {
        Message_Box_005c3230(Wonline_Text(wol_bad_key_label_7fe928,0x28c2),0,Unknown_0073c120,false);
        Close_Wonline_Wait(0x80);
        return false;
    }
    if(result!=0) {
        Message_Box_005c3230(Wonline_Text(wol_cant_create_label_7fe914,0x28c8),0,Unknown_0073c120,false);
        Close_Wonline_Wait(0x80);
        return false;
    }
    WideString title(Wonline_Text(wol_creating_label_7fe900,0x28d0));
    Open_Wait_Window_0074d4d0(4,title,false);
    Close_Wonline_Wait(0x80);
    Open_Wait_Window_0074d4d0(4,title,true);
    int index=unknown_users_b2a728.Find_Name(unknown_wstring_b26cb8);
    if(index<0) return false;
    WOL::User *user=0;
    unknown_users_b2a728.Get(user,index);
    {
        unsigned char net[4];
        unsigned char node[6];
        memset(net,0,sizeof(net));
        memset(node,0,sizeof(node));
        unsigned int ip_addr=ntohl(user->unknown_18);
        node[3]=ip_addr&0xff;
        node[2]=(ip_addr>>8)&0xff;
        node[1]=(ip_addr>>16)&0xff;
        node[0]=(ip_addr>>24)&0xff;
        IPXAddressClass address(net,node,0);
        who->Address=address;
    }
    Show_Game_Options();
    return true;
}
