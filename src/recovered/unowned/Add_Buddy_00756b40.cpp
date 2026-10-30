#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
extern "C" long __cdecl time(long *timer);
bool __fastcall Unknown_00756790(Wstring const &name);
// @ref ?Unknown_00756790@@YI_NABVWstring@@@Z=00756790
void __fastcall Unknown_00756b40(Wstring const &name)
{
    if(Unknown_00756790(name)) {
        WOL::User user;
        memset(&user,0,sizeof(user));
        strncpy(user.name,name.Peek_Buffer(),9);
        unknown_chat_a72cfc->unknown_slot56(&user);
        if(Unknown_00756790(name)) {
            Wstring friend_name(name);
            unknown_strings_b26920.Add(friend_name);
            unknown_strings_b29838.Add(friend_name);
            unknown_strings_b2a7d8.Add(friend_name);
            bool request=true;
            if(unknown_wstring_b26944.Length()>0) {
                if((unsigned long)(time(0)-unknown_b2a7f8)<5) request=false;
                else unknown_wstring_b26944.Release();
            }
            if(request && unknown_strings_b29838.Count!=0) {
                if(unknown_strings_b29838.Count>0) {
                    unknown_strings_b29838.Get(unknown_wstring_b26944,0);
                    unknown_strings_b29838.Remove_007661f0(0);
                }
                unknown_b2a7f8=time(0);
                WOL::User query;
                memset(&query,0,sizeof(query));
                strcpy(query.name,unknown_wstring_b26944.Get());
                unknown_chat_a72cfc->unknown_slot24(&query);
            }
        }
        Unknown_00757380();
    }
}
