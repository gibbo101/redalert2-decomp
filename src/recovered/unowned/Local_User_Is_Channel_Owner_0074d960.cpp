#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
bool Local_User_Is_Channel_Owner_0074d960()
{
    WOL::User *owner=0;
    for(int i=0;i<unknown_users_b2a728.Count;++i) {
        unknown_users_b2a728.Get_Copy(unknown_user_b2a658,i);
        if(unknown_user_b2a658.flags&1) {
            owner=&unknown_user_b2a658;
            break;
        }
    }
    if(!owner) return false;
    if(_stricmp(owner->name,unknown_wstring_b26cb8.Peek_Buffer())==0) return true;
    return false;
}
