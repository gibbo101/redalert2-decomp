// Point-by-value getter for the ring at original global00839C6C.
// ABuffer remains the existing project-name hypothesis.
#include "shared/blit.hpp"
unsigned short *ABuffer::Get_Buffer_Ptr(Point2D point)
{
    char *pointer=(char *)Surface->Lock(point);
    Surface->Unlock();
    char *result=(char *)((unsigned int)BufferOffset+(unsigned int)pointer);
    if((unsigned int)result>=(unsigned int)BufferTail) result=(char *)((unsigned int)result-(unsigned int)BufferSize);
    return (unsigned short *)result;
}
