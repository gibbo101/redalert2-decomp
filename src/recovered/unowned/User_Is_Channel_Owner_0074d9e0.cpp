#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
bool __fastcall User_Is_Channel_Owner_0074d9e0(Wstring const &name)
{
    WOL::User *owner=Unknown_0074DA60();
    if(!owner) return false;
    if(_stricmp(owner->name,name.Peek_Buffer())==0) return true;
    return false;
}
