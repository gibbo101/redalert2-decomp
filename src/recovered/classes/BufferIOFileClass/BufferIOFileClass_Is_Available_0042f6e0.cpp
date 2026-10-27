// BufferIOFileClass::Is_Available (0x0042F6E0, virtual slot 5)
// A file with an attached buffer is always available.
#include "shared/buffer_io_file_class.hpp"

bool BufferIOFileClass::Is_Available(int)
{
    if (UseBuffer) {
        return true;
    }
    return RawFileClass::Is_Available();
}
