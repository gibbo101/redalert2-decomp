// BufferIOFileClass::Open(char const *, int) (0x0042F720, virtual slot 8)
// Names the file, then opens it with the given rights.
#include "shared/buffer_io_file_class.hpp"

int BufferIOFileClass::Open(char const *filename, int rights)
{
    Set_Name(filename);
    return BufferIOFileClass::Open(rights);
}
