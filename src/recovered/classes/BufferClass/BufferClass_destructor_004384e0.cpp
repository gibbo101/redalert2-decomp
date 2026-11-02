// BufferClass::~BufferClass() (0x004384E0)
// Deletes an owned block.
#include "shared/buffer_class.hpp"

BufferClass::~BufferClass()
{
    if (Allocated) {
        delete[] Buffer;
    }
}
