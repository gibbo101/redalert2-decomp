// BufferIOFileClass::Free (0x0042F560)
// Detaches the cache, deleting it if Cache() allocated it, and returns the
// file to unbuffered operation.
#include "shared/buffer_io_file_class.hpp"

void BufferIOFileClass::Free()
{
    if (Buffer) {
        if (IsAllocated) {
            delete[] Buffer;
            IsAllocated = false;
        }
        Buffer = 0;
    }
    BufferSize = 0;
    IsOpen = false;
    IsCached = false;
    IsChanged = false;
    UseBuffer = false;
}
