// Clear a by-value rectangle to FFFF in the ring at original global00839C6C.
#include "shared/blit.hpp"
void ABuffer::Clear_Region_007761C0(Rect area)
{
    char *locked=(char *)Surface->Lock(Point2D(area.X,area.Y));
    Surface->Unlock();
    unsigned int pointer=(unsigned int)locked+(unsigned int)BufferOffset;
    if(pointer>=(unsigned int)BufferTail) pointer-=(unsigned int)BufferSize;
    if(area.Height>0) {
        int rows=area.Height;
        do {
            if(pointer+(unsigned int)area.Width*2u>=(unsigned int)BufferTail) {
                unsigned int first=((unsigned int)BufferTail-pointer)>>1;
                Fill_Words((unsigned short *)pointer,first,0xffff);
                Fill_Words((unsigned short *)BufferHead,area.Width-first,0xffff);
            } else {
                Fill_Words((unsigned short *)pointer,area.Width,0xffff);
            }
            pointer+=(unsigned int)Width*2u;
            if(pointer>=(unsigned int)BufferTail) pointer-=(unsigned int)BufferSize;
        } while(--rows);
    }
}
