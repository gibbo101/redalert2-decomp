#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
bool __fastcall Recall_Stored_Login_00742d80(Wstring const &requested_name)
{
    unknown_password_b2a63c.Release();
    char const *nickname;
    char const *password;
    for(int index=1;index<=32;++index) {
        if(unknown_chat_a72cfc->unknown_slot36(index,&nickname,&password)==0 && nickname && strlen(nickname) && !_stricmp(requested_name.Peek_Buffer(),nickname)) {
            unknown_wstring_b26cb8=nickname;
            unknown_password_b2a63c=password;
            unknown_7fd374=false;
            return true;
        }
    }
    unknown_wstring_b26cb8.Release();
    return false;
}
