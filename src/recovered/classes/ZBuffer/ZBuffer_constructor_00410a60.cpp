// Construct the depth buffer over a screen area: a 16-bit BSurface ring
// cleared to 0x7F, with its lock address as the ring head.
#include "shared/blit.hpp"
ZBuffer::ZBuffer(Rect area)
{
    Width=area.Width;
    Height=area.Height;
    Area=area;
    BufferSize=(int)((unsigned int)Width*(unsigned int)Height*2u);
    Surface=new BSurface(Width,Height,2);
    Surface->Fill_Rect(Rect(0,0,Width,Height),0x7f);
    BufferHead=(char *)Surface->Lock(Point2D(0,0));
    BufferOffset=0;
    MaxValue=0x8000;
    BufferTail=BufferHead+(int)((unsigned int)Width*(unsigned int)Height*2u);
    Surface->Unlock();
}
