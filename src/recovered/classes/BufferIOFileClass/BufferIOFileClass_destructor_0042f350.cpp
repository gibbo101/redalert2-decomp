// BufferIOFileClass::~BufferIOFileClass (0x0042F350)
// Releases the cache; RawFileClass's destructor then closes the file.
#include "shared/buffer_io_file_class.hpp"

BufferIOFileClass::~BufferIOFileClass()
{
    Free();
}
