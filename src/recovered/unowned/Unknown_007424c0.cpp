// Original complete2185body+7NOP, mapped before candidate. SDK Locale remains represented by its32bit ABI int.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/dialog_create.hpp"
#include "shared/crt_string.hpp"
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD,HANDLE*,BOOL,DWORD);
extern HANDLE wol_wait_events_b264f8[18];
extern char server_connecting_7fe4d0[],server_cant_connect_7fd740[],server_wdt_error_7fe4c0[],server_source_7fd62c[];
extern unsigned long server_game_version_7fd370;
void __fastcall Open_Wait_Window_0074d4d0(unsigned int,WideString const &,bool);
void __fastcall WOL_Set_Last_Valid_Persona(Wstring const &);
inline void __fastcall Close_Wonline_Wait(unsigned int flags);
int Open_Wonline_Dialog_FE_00751130();
int __fastcall Run_Control_Dialog_006011a0(int id,DLGPROC procedure,OwnerDraw::DialogControl *control);
long __stdcall Wonline_Dialog_FE_00751190(HWND,unsigned,unsigned,long);
static Wstring Server_Display_Name(char const *name);

static int Ensure_Connection_Locale(rc_ptr<PlayerProfile> const &profile)
{
    if(!profile.Get() || profile->Unknown_Value_10()==0) {
        int locale=Open_Wonline_Dialog_FE_00751130();
        if(profile.Get()) {
            profile->Set_Locale_00739950(locale,3);
            profile->Save_007395d0(unknown_wstring_b26cb8);
        }
        return locale;
    }
    return profile->Unknown_Value_10();
}

bool __fastcall Unknown_007424c0(WOL::Server *server)
{
    strcpy(server->nickname,unknown_wstring_b26cb8.Get());
    strcpy(server->password,unknown_password_b2a63c.Get());
    for(int i=0;i<18;++i) ResetEvent(wol_wait_events_b264f8[i]);
    {
        WideString connecting(StringTable::Load_String(server_connecting_7fe4d0,0,server_source_7fd62c,0x20cd));
        Open_Wait_Window_0074d4d0(0x10,connecting,false);
    }
    unknown_chat_a72cfc->RequestConnection(server,20,*(int const*)&unknown_7fd374&0xff);
    int attempts=20;
    for(;;) {
        int remaining=30000;
        DWORD event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,100);
        while(event==0x102) {
            remaining-=100;
            if(remaining<=0) goto connect_abort;
            Unknown_0073e100();
            event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,100);
        }
        ResetEvent(wol_wait_events_b264f8[event]);
        if(event==0) { Close_Wonline_Wait(~0u);return false; }
        if(event==5) {
            Popup_005c3230(StringTable::Load_String(server_cant_connect_7fd740,0,server_source_7fd62c,0x20da),0,Unknown_0073c120,0);
            Close_Wonline_Wait(~0u);return false;
        }
        if(event==18) { connect_abort: Close_Wonline_Wait(~0u);return false; }
        if(attempts--<0) {
            Popup_005c3230(StringTable::Load_String(server_cant_connect_7fd740,0,server_source_7fd62c,0x20e1),0,Unknown_0073c120,0);
            Close_Wonline_Wait(~0u);return false;
        }
        if(event==2) break;
    }
    Close_Wonline_Wait(~0u);
    unknown_chat_a72cfc->SetClientVersion(0x1000e);
    unknown_b2abd8=false;
    unknown_session_a3d298.Read_MultiPlayer_Settings();
    WolRegistryOptions options;
    options.Read_004ff200();
    rc_ptr<PlayerProfile> profile;
    if(options.unknown_004ff2c0()) profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
    else profile.Set(unknown_profile_b28cc4);
    if(unknown_a3d2a4==3 || unknown_a3d2a4==4) {
        profile->Set_Server_00739920(Server_Display_Name(server->name));
        if(options.unknown_004ff2c0()) profile->Save_007395d0(unknown_wstring_b26cb8);
    }
    strcpy(unknown_session_a3d298.Handle,unknown_wstring_b26cb8.Get());
    unknown_session_a3d298.Set_Value_00672a30(profile->Country,false);
    unknown_session_a3d298.Set_Value_00672ae0(profile->Color,false);
    unknown_session_a3d298.Write_MultiPlayer_Settings();
    WOL_Set_Last_Valid_Persona(unknown_wstring_b26cb8);
    if(unknown_ladder_client_a72d00 && strlen(unknown_ladder_address_b29018)) {
        unknown_ladder_client_a72d00->Request(unknown_ladder_address_b29018,unknown_ladder_port_b2a8ac,unknown_wstring_b26cb8.Get(),server_game_version_7fd370&0xffff00,-1,0,0);
    }
    for(int j=0;j<18;++j) ResetEvent(wol_wait_events_b264f8[j]);
    WOL::User user;
    memset(&user,0,sizeof(user));
    strcpy(user.name,unknown_wstring_b26cb8.Get());
    unknown_chat_a72cfc->RequestUserLocale(&user);
    for(;;) {
        int remaining=30000;
        DWORD event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,100);
        while(event==0x102) {
            remaining-=100;
            if(remaining<=0) goto locale_wait_abort;
            Unknown_0073e100();
            event=WaitForMultipleObjects(18,wol_wait_events_b264f8,0,100);
        }
        ResetEvent(wol_wait_events_b264f8[event]);
        if(event==0) { Close_Wonline_Wait(~0u);break; }
        if(event==5) {
            Popup_005c3230(StringTable::Load_String(server_wdt_error_7fe4c0,0,server_source_7fd62c,0x2135),0,Unknown_0073c120,0);
            Close_Wonline_Wait(~0u);break;
        }
        if(event==18) { locale_wait_abort: Close_Wonline_Wait(~0u);break; }
        if(event==14) break;
    }
    Wstring nick=unknown_wstring_b26cb8.As_Lower();
    if(unknown_channel_names_b293a0.Contains(nick)) {
        int cached_locale=0;
        {
            int *value=0;
            if(unknown_channel_names_b293a0.Get_Pointer_00767570(nick,&value) && value) cached_locale=*value;
        }
        if(cached_locale) {
        if(profile.Get() && profile->Unknown_Value_10()!=cached_locale) {
            if(profile->Unknown_Value_10()==0) {
                profile->Set_Locale_00739950(cached_locale,2);
                profile->Save_007395d0(unknown_wstring_b26cb8);
            }
            int chosen_locale=profile->Unknown_Value_10();
            unknown_chat_a72cfc->RequestSetLocale(chosen_locale);
            unknown_chat_a72cfc->RequestUserLocale(&user);
            cached_locale=chosen_locale;
            int removed;
            if(unknown_channel_names_b293a0.Remove_007675e0(nick,&removed)) unknown_channel_names_b293a0.Add_00766070(nick,cached_locale);
        }
            goto connection_done;
        }
    }
    {
        int locale=Ensure_Connection_Locale(profile);
        if(locale) {
            unknown_chat_a72cfc->RequestSetLocale(locale);
            unknown_chat_a72cfc->RequestUserLocale(&user);
            int old_locale=locale;
            int removed;
            if(unknown_channel_names_b293a0.Remove_007675e0(nick,&removed)) unknown_channel_names_b293a0.Add_00766070(nick,old_locale);
        }
    }
connection_done:
    return true;
}

// @ref ?server_cant_connect_7fd740@@3PADA=007fd740
// @ref ?server_connecting_7fe4d0@@3PADA=007fe4d0
// @ref ?server_found_debug_007fe840@@3PADA=007fe840
// @ref ?server_game_version_7fd370@@3KA=007fd370
// @ref ?server_list_wait_label_007fe670@@3PADA=007fe670
// @ref ?server_name_separator_007e6f8c@@3PADA=007e6f8c
// @ref ?server_source_7fd62c@@3PADA=007fd62c
// @ref ?server_wdt_error_7fe4c0@@3PADA=007fe4c0

