// BufferIOFileClass::Close (0x0042FDA0, virtual slot 13)
// Commits buffered changes and closes the disk file if this object opened
// it. When the file lives inside an already open file (TrueFileStart != 0),
// the containing file's own Close() runs with buffering disabled.
#include "shared/buffer_io_file_class.hpp"

void BufferIOFileClass::Close()
{
    if (UseBuffer) {
        Commit();
        if (IsDiskOpen) {
            if (TrueFileStart) {
                UseBuffer = false;
                Close();
                UseBuffer = true;
            } else {
                RawFileClass::Close();
            }
            IsDiskOpen = false;
        }
        IsOpen = false;
    } else {
        RawFileClass::Close();
    }
}
