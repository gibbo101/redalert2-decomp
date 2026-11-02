// StaticBufferClass::~StaticBufferClass() (0x0069A1C0): frees the storage.
#define STATIC_BUFFER_DECLARE_LIFETIME
#include "shared/rect.hpp"
#include "shared/surface_region.hpp"
#include "shared/static_buffer.hpp"
#include "shared/crt_memory.hpp"

StaticBufferClass::~StaticBufferClass()
{
    if (Buffer != 0) {
        delete [] Buffer;
    }
}
