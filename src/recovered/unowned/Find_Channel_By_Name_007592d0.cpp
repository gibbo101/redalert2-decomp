#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
bool __fastcall Find_Channel_By_Name_007592d0(Wstring const &name,WolChannelArray const &channels,WOL::Channel &channel)
{
    memset(&channel,0,sizeof(channel));
    for(int i=0;i<channels.Count;++i) {
        channels.Get(channel,i);
        if(_stricmp(channel.name,name.Peek_Buffer())==0) return true;
    }
    memset(&channel,0,sizeof(channel));
    return false;
}
