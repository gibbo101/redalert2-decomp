#include "shared/wol_sink.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"
extern "C" int __cdecl swprintf(wchar_t *,wchar_t const *,...);
extern int wol_connection_status_b26a2c[];
extern char wol_source_file_007fd62c[];
extern char connect_player_debug_007fee6c[];
extern char connect_player_label_007fee50[];
extern char connect_remote_debug_007fee30[];
extern char connect_remote_label_007fee18[];
extern char connect_proxy_debug_007fedf4[];
extern char connect_proxy_label_007fedd4[];
extern char connect_peer_proxy_debug_007fed9c[];
extern char connect_peer_proxy_label_007fed7c[];
extern char connect_host_debug_007fed3c[];
extern char connect_host_label_007fed24[];
extern char connect_unknown_label_007fed10[];
// @ref _swprintf=00783764
// @ref ?wol_connection_status_b26a2c@@3PAHA=00b26a2c
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?connect_player_debug_007fee6c@@3PADA=007fee6c
// @ref ?connect_player_label_007fee50@@3PADA=007fee50
// @ref ?connect_remote_debug_007fee30@@3PADA=007fee30
// @ref ?connect_remote_label_007fee18@@3PADA=007fee18
// @ref ?connect_proxy_debug_007fedf4@@3PADA=007fedf4
// @ref ?connect_proxy_label_007fedd4@@3PADA=007fedd4
// @ref ?connect_peer_proxy_debug_007fed9c@@3PADA=007fed9c
// @ref ?connect_peer_proxy_label_007fed7c@@3PADA=007fed7c
// @ref ?connect_host_debug_007fed3c@@3PADA=007fed3c
// @ref ?connect_host_label_007fed24@@3PADA=007fed24
// @ref ?connect_unknown_label_007fed10@@3PADA=007fed10
void Report_Connection_Errors_0074dd50()
{
    wchar_t message[256];
    WOL::User *owner=0;
    int i;
    for(i=0;i<unknown_users_b2a728.Count;++i) {
        unknown_users_b2a728.Get_Copy(unknown_user_b2a658,i);
        if(unknown_user_b2a658.flags&1) {
            owner=&unknown_user_b2a658;
            break;
        }
    }
    if(owner) {
        int owner_index=-1;
        for(i=0;i<unknown_players_a3fa7c.Count();++i) {
            if(!_stricmp(Unknown_006FA120(unknown_players_a3fa7c[i]->Name),owner->name)) {
                owner_index=i;
                break;
            }
        }
        bool reported=false;
        for(i=0;i<unknown_players_a3fa7c.Count();++i) {
            switch(wol_connection_status_b26a2c[i]) {
            case 0:
                reported=true;
                Debug_Printf(connect_player_debug_007fee6c,Unknown_006FA120(unknown_players_a3fa7c[i]->Name));
                swprintf(message,StringTable::Load_String(connect_player_label_007fee50,0,wol_source_file_007fd62c,0x41fe),unknown_players_a3fa7c[i]->Name);
                Unknown_005C2C80(unknown_color_7a7360,message);
                break;
            case 1:
                reported=true;
                Debug_Printf(connect_remote_debug_007fee30,Unknown_006FA120(unknown_players_a3fa7c[i]->Name));
                swprintf(message,StringTable::Load_String(connect_remote_label_007fee18,0,wol_source_file_007fd62c,0x4208),unknown_players_a3fa7c[i]->Name);
                Unknown_005C2C80(unknown_color_7a7360,message);
                break;
            case 2:
                reported=true;
                if(i==owner_index) {
                    Debug_Printf(connect_proxy_debug_007fedf4);
                    Unknown_005C2C80(unknown_color_7a7360,StringTable::Load_String(connect_proxy_label_007fedd4,0,wol_source_file_007fd62c,0x4213));
                } else {
                    Debug_Printf(connect_peer_proxy_debug_007fed9c,Unknown_006FA120(unknown_players_a3fa7c[i]->Name));
                    swprintf(message,StringTable::Load_String(connect_peer_proxy_label_007fed7c,0,wol_source_file_007fd62c,0x4216),unknown_players_a3fa7c[i]->Name);
                    Unknown_005C2C80(unknown_color_7a7360,message);
                }
                break;
            case 3:
                reported=true;
                Debug_Printf(connect_host_debug_007fed3c);
                Unknown_005C2C80(unknown_color_7a7360,StringTable::Load_String(connect_host_label_007fed24,0,wol_source_file_007fd62c,0x4221));
                break;
            }
        }
        if(!reported) Unknown_005C2C80(unknown_color_7a7360,StringTable::Load_String(connect_unknown_label_007fed10,0,wol_source_file_007fd62c,0x422e));
    }
}
