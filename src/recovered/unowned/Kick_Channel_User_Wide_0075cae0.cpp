#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
void __fastcall Kick_Channel_User_Wide_0075cae0(wchar_t const *name)
{
    if(name) {
        Wstring narrow=Narrow_Copy_00771280(name);
        WOL::User user;
        user.flags=0;
        for(int i=0;i<unknown_users_b2a728.Count;++i) {
            unknown_users_b2a728.Get_Copy(user,i);
            if(_stricmp(narrow.Peek_Buffer(),user.name)==0) {
                unknown_chat_a72cfc->unknown_slot21(&user);
                break;
            }
        }
    }
}
