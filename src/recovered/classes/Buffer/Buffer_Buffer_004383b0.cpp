// Buffer::Buffer(Buffer const &) (0x004383B0)
// References the source's memory without owning it.
#include "shared/buffer.hpp"

Buffer::Buffer(Buffer const &buffer) :
    IsAllocated(false)
{
    BufferPtr = buffer.BufferPtr;
    Size = buffer.Size;
}
