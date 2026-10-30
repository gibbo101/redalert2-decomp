#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern bool receiving_host_preview_00b2ac46;
extern char host_preview_debug_007ff8d8[];
// @ref ?receiving_host_preview_00b2ac46@@3_NA=00b2ac46
// @ref ?host_preview_debug_007ff8d8@@3PADA=007ff8d8
// Existing canonical Poke_The_Host_00750f60 uses this same User* interface to 74D7D0.
// @ref ?Unknown_0074d7d0@@YIXPAUUser@WOL@@@Z=0074d7d0
bool __fastcall Receive_Host_Map_Preview_00750d10()
{
    IPXAddressClass address;
    if(unknown_game_channel_b299c0.unknown_00 && unknown_users_b2a728.Count>=2) {
        WOL::User *owner=0;
        for(int i=0;i<unknown_users_b2a728.Count;++i) {
            unknown_users_b2a728.Get_Copy(unknown_user_b2a658,i);
            if(unknown_user_b2a658.flags&1) {
                owner=&unknown_user_b2a658;
                break;
            }
        }
        if(owner && !_stricmp(owner->name,unknown_wstring_b26cb8.Peek_Buffer())) return false;
        if(unknown_b2ac40==0 && unknown_ipx_manager_a40978.Global_Num_Receive()) {
            Service_Game_IO_00481fb0();
            UnknownGlobalPacket packet;
            int length=sizeof(packet);
            unsigned short product;
            if(unknown_ipx_manager_a40978.unknown_525af0(0,&packet,&length,&address,&product,0) && packet.Command==25) {
                void *dialog=Unknown_00735940(0xc9);
                if(dialog) ShowWindow(GetDlgItem((HWND)dialog,0x468),1);
                WOL::User user;
                unknown_users_b2a728.Get_Copy(user,0);
                user.next=0;
                Unknown_0074d7d0(&user);
                if(unknown_ipx_manager_a40978.Get_Global_Message(&packet,&length,&address,&product) && packet.Command==25 && address.unknown_523690(unknown_address_a3db2c) && product==0xaa03) {
                    owner=0;
                    for(int i=0;i<unknown_users_b2a728.Count;++i) {
                        unknown_users_b2a728.Get_Copy(unknown_user_b2a658,i);
                        if(unknown_user_b2a658.flags&1) {
                            owner=&unknown_user_b2a658;
                            break;
                        }
                    }
                    if(owner && !_stricmp(packet.Name,owner->name)) {
                        Debug_Printf(host_preview_debug_007ff8d8);
                        unknown_ipx_manager_a40978.Set_Timing(50,(unsigned long)-1,5000,true);
                        receiving_host_preview_00b2ac46=true;
                        Download_Map_Preview_005c7970();
                        receiving_host_preview_00b2ac46=false;
                        unknown_ipx_manager_a40978.Set_Timing(30,(unsigned long)-1,600,true);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
