// BufferIOFileClass::BufferIOFileClass() (0x0042F2F0)
// An unbuffered, unnamed file.
#include "shared/buffer_io_file_class.hpp"

BufferIOFileClass::BufferIOFileClass() :
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
}
