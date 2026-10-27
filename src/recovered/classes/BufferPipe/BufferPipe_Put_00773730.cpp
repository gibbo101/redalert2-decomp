#include "shared/buffer_pipe.hpp"
#include "shared/crt_memory.hpp"
int BufferPipe::Put(void const *source,int length)
{
    int amount=0;
    if(Storage.Get_Buffer() && source && length>0) {
        amount=length;
        if(Storage.Get_Size()!=0) {
            int remaining=Storage.Get_Size()-Position;
            amount=length<remaining ? length : remaining;
        }
        if(amount>0) memmove((char *)Storage.Get_Buffer()+Position,source,amount);
        Position+=amount;
    }
    return amount;
}
