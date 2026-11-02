// BufferClass::BufferClass(void *ptr, int size) (0x00438470)
// Uses the caller's block, or allocates and owns one of the size.
#include "shared/buffer_class.hpp"

BufferClass::BufferClass(void *ptr, int size)
{
    Size = size;
    if (ptr) {
        Buffer = (unsigned char *)ptr;
        Allocated = false;
    } else {
        Buffer = new unsigned char[Size];
        Allocated = true;
    }
}
