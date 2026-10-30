#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
extern int unknown_last_nickname_slot_a3d554;
// @ref ?unknown_last_nickname_slot_a3d554@@3HA=00a3d554
int __fastcall Save_Nickname_00745320(char const *name,char const *password,bool mangle,int locale)
{
    int slot=0;
    char const *nick;
    char const *stored_password;
    for(int i=1;i<=32;++i) {
        nick=0;
        stored_password=0;
        if(unknown_chat_a72cfc->unknown_slot36(i,&nick,&stored_password)==0 && nick && !strcmp(nick,name)) {
            slot=i;
            break;
        }
    }
    if(slot==0) {
        for(int i=1;i<=32;++i) {
            nick=0;
            stored_password=0;
            if(unknown_chat_a72cfc->unknown_slot36(i,&nick,&stored_password)!=0 || !nick || strlen(nick)==0) {
                slot=i;
                break;
            }
        }
    }
    if(slot==0) {
        int next=unknown_last_nickname_slot_a3d554;
        if(next==-1) next=1;
        slot=next++;
        unknown_last_nickname_slot_a3d554=next;
        if(next>32) unknown_last_nickname_slot_a3d554=1;
    }
    if(slot) {
        unknown_chat_a72cfc->unknown_slot37(slot,name,password,(unsigned char)mangle);
        unknown_chat_a72cfc->unknown_slot50(slot,locale);
    }
    return slot;
}
