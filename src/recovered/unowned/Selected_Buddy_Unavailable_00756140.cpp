#include "shared/wol_sink.hpp"
bool Selected_Buddy_Unavailable_00756140()
{
    if(unknown_wstring_b29cd4.Length()==0) return false;
    unsigned int status=0;
    unknown_names_b29848.Get_Value(unknown_wstring_b29cd4,status);
    if((int)status>=0 && (int)status<=2) return false;
    return true;
}
