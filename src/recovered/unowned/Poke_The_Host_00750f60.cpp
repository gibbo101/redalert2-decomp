#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_address.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern char wol_host_address_debug_7ff904[];
void __fastcall Unknown_006fa0f0(char *destination,wchar_t const *source,int count);
// @ref ?wol_host_address_debug_7ff904@@3PADA=007ff904
// @ref ?Unknown_006fa0f0@@YIXPADPBGH@Z=006fa0f0
// @ref ?Unknown_0074d7d0@@YIXPAUUser@WOL@@@Z=0074d7d0
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
void __fastcall Poke_The_Host_00750f60()
{
    if(unknown_game_mode_a3d298!=4) {
        IPXAddressClass address;
        if(unknown_users_b2a728.Count>=2) {
            WOL::User *owner=0;
            for(int i=0;i<unknown_users_b2a728.Count;++i) {
                unknown_users_b2a728.Get(unknown_user_b2a658,i);
                if(unknown_user_b2a658.flags&1) {
                    owner=&unknown_user_b2a658;
                    break;
                }
            }
            if(owner && !_stricmp(owner->name,unknown_wstring_b26cb8.Peek_Buffer())) return;
            if(unknown_b2ac40==0 && unknown_game_channel_b299c0.unknown_00!=0) {
                WOL::User user;
                unknown_users_b2a728.Get_Copy(user,0);
                user.next=0;
                Unknown_0074d7d0(&user);
                Service_Game_IO_00481fb0();
                unknown_ipx_manager_a40978.Set_Timing(50,(unsigned long)-1,5000,true);
                Debug_Printf(wol_host_address_debug_7ff904,unknown_address_a3db2c.As_String_00523840());
                UnknownGlobalPacket packet;
                memset(&packet,0,sizeof(packet));
                packet.Command=13;
                Unknown_006fa0f0(packet.Name,unknown_players_a3fa7c[0]->Name,-1);
                owner=0;
                for(int i=0;i<unknown_users_b2a728.Count;++i) {
                    unknown_users_b2a728.Get_Copy(unknown_user_b2a658,i);
                    if(unknown_user_b2a658.flags&1) {
                        owner=&unknown_user_b2a658;
                        break;
                    }
                }
                if(owner) unknown_ipx_manager_a40978.unknown_5259a0(&packet,sizeof(packet),1,Unknown_006FA180(owner->name));
                Service_Game_IO_00481fb0();
            }
        }
    }
}
