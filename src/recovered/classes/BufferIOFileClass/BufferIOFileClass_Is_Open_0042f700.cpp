// BufferIOFileClass::Is_Open (0x0042F700, virtual slot 6)
// Open when logically opened through the buffer, or when the disk handle is
// open (RawFileClass::Is_Open, inlined in the original).
#include "shared/buffer_io_file_class.hpp"

bool BufferIOFileClass::Is_Open() const
{
    if (IsOpen && UseBuffer) {
        return true;
    }
    return Handle != INVALID_HANDLE_VALUE;
}
