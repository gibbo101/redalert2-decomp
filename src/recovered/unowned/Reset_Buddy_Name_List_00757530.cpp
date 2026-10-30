#include "shared/wol_sink.hpp"
void Reset_Buddy_Name_List_00757530()
{
    unknown_strings_b2a7d8.Clear();
    for(int i=0;i<unknown_strings_b26920.Count;++i) {
        Wstring name;
        unknown_strings_b26920.Get(name,i);
        unknown_strings_b2a7d8.Add_Tail(name);
    }
    Unknown_00757380();
}
