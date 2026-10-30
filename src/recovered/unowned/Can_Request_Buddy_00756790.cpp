#include "shared/wol_sink.hpp"
extern char wol_invalid_name_chars_7fea20[];
// @ref ?wol_invalid_name_chars_7fea20@@3PADA=007fea20
bool __fastcall Unknown_00756790(Wstring const &name)
{
    Wstring lower_name(name);
    lower_name.To_Lower();
    if(name.Length()==0) return false;
    if(lower_name.As_Lower()==unknown_wstring_b26cb8.As_Lower()) return false;
    if(name.Contains_Any(wol_invalid_name_chars_7fea20)) return false;
    for(int i=0;i<unknown_strings_b26920.Count;++i) {
        Wstring other;
        unknown_strings_b26920.Get(other,i);
        other.To_Lower();
        if(other==lower_name) return false;
    }
    return true;
}
