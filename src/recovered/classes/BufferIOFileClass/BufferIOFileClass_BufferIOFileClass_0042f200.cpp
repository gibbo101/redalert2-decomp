// BufferIOFileClass::BufferIOFileClass(char const *) (0x0042F200)
// An unbuffered file with the given name; Cache() attaches a buffer later.
#include "shared/buffer_io_file_class.hpp"

BufferIOFileClass::BufferIOFileClass(char const *filename) :
    IsAllocated(false),
    IsOpen(false),
    IsDiskOpen(false),
    IsCached(false),
    IsChanged(false),
    UseBuffer(false),
    BufferRights(0),
    Buffer(0),
    BufferSize(0),
    BufferPos(0),
    BufferFilePos(0),
    BufferChangeBeg(-1),
    BufferChangeEnd(-1),
    FileSize(0),
    FilePos(0),
    TrueFileStart(0)
{
    Set_Name(filename);
}
