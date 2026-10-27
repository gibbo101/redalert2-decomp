// Buffer::Buffer(long) (0x00438380)
// Allocates and owns a block of the given size (empty when size <= 0).
#include "shared/buffer.hpp"

Buffer::Buffer(long size) :
    BufferPtr(0),
    Size(size),
    IsAllocated(false)
{
    if (Size > 0) {
        BufferPtr = new char[Size];
        IsAllocated = true;
    }
}
