// Address of the depth value for a screen point: the lock address of the
// backing surface moved by the ring origin, wrapped at the ring end.
#include "shared/blit.hpp"
unsigned short *ZBuffer::Get_Buffer_Ptr(Point2D point)
{
    char *pointer=(char *)Surface->Lock(point);
    Surface->Unlock();
    char *result=(char *)((unsigned int)BufferOffset+(unsigned int)pointer);
    if((unsigned int)result>=(unsigned int)BufferTail) result=(char *)((unsigned int)result-(unsigned int)BufferSize);
    return (unsigned short *)result;
}
