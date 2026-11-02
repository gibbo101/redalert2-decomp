// StaticBufferClass::StaticBufferClass(int size) (0x0069A1A0; was UnknownBuffer_0069a1a0): size bytes of storage,
// Buffer and Current at their start.
#define STATIC_BUFFER_DECLARE_LIFETIME
#include "shared/rect.hpp"
#include "shared/surface_region.hpp"
#include "shared/static_buffer.hpp"
#include "shared/crt_memory.hpp"

StaticBufferClass::StaticBufferClass(int size)
{
    Capacity = size;
    unsigned char *data = new unsigned char[size];
    Buffer = data;
    Current = data;
}
