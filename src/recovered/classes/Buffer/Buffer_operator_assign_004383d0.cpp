// Buffer::operator= (0x004383D0)
// Releases an owned block, then references the source's memory without
// owning it.
#include "shared/buffer.hpp"

Buffer &Buffer::operator=(Buffer const &buffer)
{
    if (&buffer != this) {
        if (IsAllocated) {
            delete[] BufferPtr;
        }
        IsAllocated = false;
        BufferPtr = buffer.BufferPtr;
        Size = buffer.Size;
    }
    return *this;
}
