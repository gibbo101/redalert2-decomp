#include "shared/cache_straw.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Get@Straw@@UAEHPAXH@Z=0069b0a0
int CacheStraw::Get(void *buffer,int length)
{
 int total=0;
 if(BufferPtr.Is_Valid() && buffer && length>0) {
  do {
   if(Length>0) {
    int count=Length<length ? Length : length;
    memmove(buffer,(char *)BufferPtr.Get_Buffer()+Index,count);
    length-=count;
    Index+=count;
    total+=count;
    Length-=count;
    buffer=(char *)buffer+count;
   }
   if(length==0) break;
   Length=Straw::Get(BufferPtr.Get_Buffer(),BufferPtr.Get_Size());
   Index=0;
  } while(Length && length>0);
 }
 return total;
}
