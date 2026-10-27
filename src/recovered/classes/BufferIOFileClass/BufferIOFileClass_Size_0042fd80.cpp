// BufferIOFileClass::Size (0x0042FD80, virtual slot 11)
// The logical size while buffered; otherwise the disk size.
#include "shared/buffer_io_file_class.hpp"

long BufferIOFileClass::Size()
{
    if (IsOpen && UseBuffer) {
        return FileSize;
    }
    return RawFileClass::Size();
}
