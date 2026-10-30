#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
extern "C" long __cdecl time(long *);
// @ref _time=0078387f
void Service_Buddy_Find_Queue_00756610()
{
    if(unknown_wstring_b26944.Length()>0) {
        if((unsigned long)(time(0)-unknown_b2a7f8)<5) return;
        unknown_wstring_b26944.Release();
    }
    if(unknown_strings_b29838.Count!=0) {
        if(unknown_strings_b29838.Count>0) {
            unknown_strings_b29838.Get(unknown_wstring_b26944,0);
            unknown_strings_b29838.Remove(0);
        }
        unknown_b2a7f8=time(0);
        WOL::User user;
        memset(&user,0,sizeof(user));
        strcpy(user.name,unknown_wstring_b26944.Get());
        unknown_chat_a72cfc->unknown_slot24(&user);
    }
}
