#include "shared/wol_sink.hpp"
#include "shared/wol_registry_options.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/debug_printf.hpp"
void __fastcall Reset_Server_List_00600db0(HWND list);
extern char no_server_text_007fe854[],server_found_debug_007fe840[],server_name_separator_007e6f8c[];
// @ref ?Reset_Server_List_00600db0@@YIXPAUHWND__@@@Z=00600db0
// @ref ?no_server_text_007fe854@@3PADA=007fe854
// @ref ?server_found_debug_007fe840@@3PADA=007fe840
// @ref ?server_name_separator_007e6f8c@@3PADA=007e6f8c
static Wstring Server_Display_Name(char const *name)
{
    Wstring full(name);
    Wstring prefix;
    int split=full.Get_Token(0,server_name_separator_007e6f8c,prefix);
    if(split>=0) full.Remove(0,split+1);
    return full;
}
bool __fastcall Populate_Server_Choices_007454c0(HWND list,bool combo)
{
    if(combo) unknown_reset_combo_6007f0(list);
    else Reset_Server_List_00600db0(list);
    if(unknown_servers_b2a700.Count==1) {
        if(combo) SendMessageA(list,0x4bc,0,(LPARAM)no_server_text_007fe854);
        else SendMessageA(list,0x4c8,0,(LPARAM)no_server_text_007fe854);
        EnableWindow(list,false);
        return false;
    }
    Wstring preferred;
    WolRegistryOptions options;
    options.Read_004ff200();
    rc_ptr<PlayerProfile> profile;
    if(options.unknown_004ff2c0()) profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
    else profile.Set(unknown_profile_b28cc4);
    if(profile.Get()) preferred=profile->Server;
    EnableWindow(list,true);
    int selected=-1;
    for(int i=1;i<unknown_servers_b2a700.Count;++i) {
        WOL::Server *server=0;
        unknown_servers_b2a700.Get(server,i);
        Debug_Printf(server_found_debug_007fe840,server->name);
        Wstring display=Server_Display_Name(server->name);
        int row;
        if(combo) {
            row=SendMessageA(list,0x4bc,0,(LPARAM)display.Peek_Buffer());
            SendMessageA(list,0x151,row,i);
        } else {
            row=SendMessageA(list,0x4c8,0,(LPARAM)display.Peek_Buffer());
            SendMessageA(list,0x19a,row,i);
        }
        if(preferred.Length()>0) {
            bool match=preferred.As_Lower()==display.As_Lower();
            if(match) {
                selected=row;
                unknown_irc_index_b292d8=i;
                unknown_irc_index_b2a7f4=i;
            }
        }
    }
    if(selected==-1) selected=0;
    if(combo) SendMessageA(list,0x14e,selected,0);
    else {
        SendMessageA(list,0x186,selected,0);
        SendMessageA(list,0x197,selected,0);
    }
    return true;
}
