#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern char wol_user_count_debug_007ffea0[],wol_skip_owner_debug_007ffe74[],wol_skip_local_debug_007ffe50[],wol_queue_name_debug_007ffe2c[];
// @ref ?wol_user_count_debug_007ffea0@@3PADA=007ffea0
// @ref ?wol_skip_owner_debug_007ffe74@@3PADA=007ffe74
// @ref ?wol_skip_local_debug_007ffe50@@3PADA=007ffe50
// @ref ?wol_queue_name_debug_007ffe2c@@3PADA=007ffe2c
void __fastcall Collect_Remote_Player_Names_0075a6c0()
{
    WOL::User user;
    memset(&user,0,sizeof(user));
    Debug_Printf(wol_user_count_debug_007ffea0,unknown_users_b2a728.Count);
    for(int i=0;i<unknown_users_b2a728.Count;++i) {
        unknown_users_b2a728.Get_Copy(user,i);
        if(user.flags&1) Debug_Printf(wol_skip_owner_debug_007ffe74,user.name);
        else if(!_stricmp(user.name,unknown_wstring_b26cb8.Get())) Debug_Printf(wol_skip_local_debug_007ffe50,user.name);
        else {
            Wstring name(user.name);
            Debug_Printf(wol_queue_name_debug_007ffe2c,name.Get());
            unknown_strings_b29980.Add_Tail(name);
        }
    }
}
