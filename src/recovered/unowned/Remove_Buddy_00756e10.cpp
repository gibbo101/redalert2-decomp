#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_channels_b29478@@3VWolChannelDictionary@@A=00b29478
// @ref ?unknown_names_b29848@@3VWolNameTable@@A=00b29848
void __fastcall Unknown_00756e10(Wstring const &name)
{
    for(int i=0;i<unknown_strings_b26920.Count;++i) {
        Wstring other;
        unknown_strings_b26920.Get(other,i);
        if(other==name) {
            unknown_strings_b26920.Remove(i);
            Wstring key(name);
            WOL::Channel channel;
            unknown_channels_b29478.Remove_00767d60(key,&channel);
            unknown_names_b29848.Remove_Name(key);
            WOL::User user;
            memset(&user,0,sizeof(user));
            strncpy(user.name,name.Peek_Buffer(),9);
            unknown_chat_a72cfc->unknown_slot57(&user);
            return;
        }
    }
}
