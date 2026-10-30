#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
void __fastcall Kick_Channel_User_0075ca60(Wstring const &name)
{
    WOL::User user;
    user.flags=0;
    for(int i=0;i<unknown_users_b2a728.Count;++i) {
        unknown_users_b2a728.Get_Copy(user,i);
        if(_stricmp(name.Peek_Buffer(),user.name)==0) {
            unknown_chat_a72cfc->unknown_slot21(&user);
            break;
        }
    }
}
