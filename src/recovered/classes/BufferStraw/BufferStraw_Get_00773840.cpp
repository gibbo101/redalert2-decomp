#include "shared/buffer_straw.hpp"
#include "shared/crt_memory.hpp"
int BufferStraw::Get(void *destination,int length)
{
    int amount=0;
    if(Storage.Get_Buffer() && destination && length>0) {
        amount=length;
        if(Storage.Get_Size()!=0) {
            int remaining=Storage.Get_Size()-Position;
            amount=length<remaining ? length : remaining;
        }
        if(amount>0) memmove(destination,(char const *)Storage.Get_Buffer()+Position,amount);
        Position+=amount;
    }
    return amount;
}
