#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
bool __fastcall User_Is_Channel_Owner_0074d9e0(Wstring const &name)
{
    WOL::User *owner=0;
    for(int index=0;index<unknown_users_b2a728.Count;++index) {
        unknown_users_b2a728.Get_Copy(unknown_user_b2a658,index);
        if(unknown_user_b2a658.flags&1) {
            owner=&unknown_user_b2a658;
            break;
        }
    }
    if(!owner) return false;
    if(_stricmp(owner->name,name.Peek_Buffer())==0) return true;
    return false;
}
