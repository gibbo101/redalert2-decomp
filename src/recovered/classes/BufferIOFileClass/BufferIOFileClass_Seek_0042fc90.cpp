// BufferIOFileClass::Seek (0x0042FC90, virtual slot 10)
// Moves the logical position, clamped to [0, FileSize]. Within the current
// buffer window only BufferPos moves; outside it, changes are committed and
// the disk position follows. Positions at or beyond TrueFileStart are taken
// as absolute disk positions and answered the same way.
#include "shared/buffer_io_file_class.hpp"

long BufferIOFileClass::Seek(long position, int origin)
{
    if (UseBuffer) {
        bool adjusted = false;
        switch (origin) {
        case FILE_SEEK_START:
            FilePos = 0;
            break;
        case FILE_SEEK_END:
            FilePos = FileSize;
            break;
        }
        if (TrueFileStart && position >= TrueFileStart) {
            position -= TrueFileStart;
            adjusted = true;
        }
        FilePos += position;
        if (FilePos < 0) {
            FilePos = 0;
        }
        if (FilePos > FileSize) {
            FilePos = FileSize;
        }
        if (FileSize <= BufferSize) {
            BufferPos = FilePos;
        } else if (FilePos >= BufferFilePos && FilePos < BufferFilePos + BufferSize) {
            BufferPos = FilePos - BufferFilePos;
        } else {
            Commit();
            if (TrueFileStart) {
                UseBuffer = false;
                Seek(FilePos, FILE_SEEK_START);
                UseBuffer = true;
            } else {
                RawFileClass::Seek(FilePos, FILE_SEEK_START);
            }
            IsCached = false;
        }
        if (TrueFileStart && adjusted) {
            return FilePos + TrueFileStart;
        }
        return FilePos;
    }
    return RawFileClass::Seek(position, origin);
}
