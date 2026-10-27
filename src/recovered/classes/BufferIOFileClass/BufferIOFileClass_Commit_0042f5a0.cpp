// BufferIOFileClass::Commit (0x0042F5A0)
// Writes the changed part of the buffer back to disk, opening the disk file
// temporarily if needed. Returns whether anything was written.
#include "shared/buffer_io_file_class.hpp"

bool BufferIOFileClass::Commit()
{
    if (UseBuffer && IsChanged) {
        long size = BufferChangeEnd - BufferChangeBeg;
        if (IsDiskOpen) {
            RawFileClass::Seek(TrueFileStart + BufferFilePos + BufferChangeBeg, FILE_SEEK_START);
            RawFileClass::Write(Buffer, size);
            RawFileClass::Seek(TrueFileStart + FilePos, FILE_SEEK_START);
        } else {
            RawFileClass::Open(FILE_RIGHTS_READ);
            RawFileClass::Seek(TrueFileStart + BufferFilePos + BufferChangeBeg, FILE_SEEK_START);
            RawFileClass::Write(Buffer, size);
            RawFileClass::Close();
        }
        IsChanged = false;
        return true;
    }
    return false;
}
