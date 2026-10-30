#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
int __fastcall Compare_Channel_Users_007416d0(WOL::User const *first,WOL::User const *second)
{
    WOL::User const *users[2]={first,second};
    int ranks[2]={0,0};
    for(int i=0;i<2;++i) {
        unsigned int flags=users[i]->flags;
        if(flags&1) ranks[i]+=4;
        if(flags&2) ranks[i]+=2;
    }
    if(ranks[0]<ranks[1]) return 1;
    if(ranks[0]>ranks[1]) return -1;
    return _stricmp(first->name,second->name);
}
