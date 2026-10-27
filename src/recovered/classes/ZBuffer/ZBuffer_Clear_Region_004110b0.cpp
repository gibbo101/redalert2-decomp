// Clear a by-value screen rectangle of the ring to 0x7F (empty depth),
// splitting each row where it wraps past the ring end.
#include "shared/blit.hpp"
void ZBuffer::Clear_Region_004110B0(Rect area)
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
                Fill_Words((unsigned short *)pointer,first,0x7f);
                Fill_Words((unsigned short *)BufferHead,area.Width-first,0x7f);
            } else {
                Fill_Words((unsigned short *)pointer,area.Width,0x7f);
            }
            pointer+=(unsigned int)Width*2u;
            if(pointer>=(unsigned int)BufferTail) pointer-=(unsigned int)BufferSize;
        } while(--rows);
    }
}
