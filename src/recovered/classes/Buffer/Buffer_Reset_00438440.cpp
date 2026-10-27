// Buffer::Reset (0x00438440)
// Deletes an owned block and leaves the buffer empty and unowned.
#include "shared/buffer.hpp"

void Buffer::Reset()
{
    if (IsAllocated) {
        delete[] BufferPtr;
    }
    BufferPtr = 0;
    Size = 0;
    IsAllocated = false;
}
