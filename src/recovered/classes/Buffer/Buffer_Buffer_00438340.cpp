// Buffer::Buffer(void const *, long) (0x00438340)
// References caller memory (read-only pointer); with no pointer but a positive
// size, allocates and owns a block of that size instead. The three pointer
// constructors compile to identical code; callers distinguish them (the
// default Buffer() binds to the void * one at 0x004382C0).
#include "shared/buffer.hpp"

Buffer::Buffer(void const * pointer, long size) :
    BufferPtr((char *)pointer),
    Size(size),
    IsAllocated(false)
{
    if (BufferPtr == 0 && Size > 0) {
        BufferPtr = new char[Size];
        IsAllocated = true;
    }
}
