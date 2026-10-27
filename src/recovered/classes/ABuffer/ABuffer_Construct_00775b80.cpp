// Construct the 16-bit ring stored at original global 00839C6C.
// ABuffer is the existing project name hypothesis, not an asserted RTTI identity.
#include "shared/blit.hpp"
ABuffer::ABuffer(Rect area)
{
    Width=area.Width;
    Height=area.Height;
    Area=area;
    BufferSize=(int)((unsigned int)Width*(unsigned int)Height*2u);
    Surface=new BSurface(Width,Height,2);
    Surface->Fill_Rect(Rect(0,0,Width,Height),0xffff);
    BufferHead=(char *)Surface->Lock(Point2D(0,0));
    BufferOffset=0;
    MaxValue=0x8000;
    BufferTail=BufferHead+(int)((unsigned int)Width*(unsigned int)Height*2u);
    Surface->Unlock();
}
