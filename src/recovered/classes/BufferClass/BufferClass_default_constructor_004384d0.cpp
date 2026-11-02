// BufferClass::BufferClass() (0x004384D0)
// An empty buffer.
#include "shared/buffer_class.hpp"

BufferClass::BufferClass()
{
    Buffer = 0;
    Size = 0;
    Allocated = false;
}
