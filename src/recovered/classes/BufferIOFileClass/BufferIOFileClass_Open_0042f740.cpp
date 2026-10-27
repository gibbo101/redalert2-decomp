// BufferIOFileClass::Open(int) (0x0042F740, virtual slot 7)
// Opens the file logically. Unbuffered files open on disk directly. A
// buffered file small enough to be cached whole is served from memory for
// reading; otherwise the disk file is opened too. Opening for writing first
// creates (truncates) the file and then reopens it read/write.
#include "shared/buffer_io_file_class.hpp"

int BufferIOFileClass::Open(int rights)
{
    BufferIOFileClass::Close();
    if (UseBuffer) {
        BufferRights = rights;
        if (rights != FILE_RIGHTS_READ || FileSize > BufferSize) {
            if (rights == FILE_RIGHTS_WRITE) {
                RawFileClass::Open(FILE_RIGHTS_WRITE);
                RawFileClass::Close();
                rights = FILE_RIGHTS_READ_WRITE;
                TrueFileStart = 0;
            }
            if (TrueFileStart) {
                UseBuffer = false;
                Open(rights);
                UseBuffer = true;
            } else {
                RawFileClass::Open(rights);
            }
            IsDiskOpen = true;
            if (BufferRights == FILE_RIGHTS_WRITE) {
                FileSize = 0;
            }
        } else {
            IsDiskOpen = false;
        }
        BufferPos = 0;
        BufferFilePos = 0;
        BufferChangeBeg = -1;
        BufferChangeEnd = -1;
        FilePos = 0;
        IsOpen = true;
    } else {
        RawFileClass::Open(rights);
    }
    return true;
}
