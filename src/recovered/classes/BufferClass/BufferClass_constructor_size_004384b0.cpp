// BufferClass::BufferClass(int size) (0x004384B0)
// Allocates and owns a block of the size.
#include "shared/buffer_class.hpp"

BufferClass::BufferClass(int size)
{
    Size = size;
    Buffer = new unsigned char[Size];
    Allocated = true;
}
