// long RAMFileClass::Seek(long position, int origin) (0x006384E0, slot 10)
// Moves the position, clamped to the data (or, open for writing, to the
// capacity); the data grows to a position past its end.
#include "shared/ram_file_class.hpp"

long RAMFileClass::Seek(long position, int origin)
{
    if (Buffer == 0 || !Is_Open()) {
        return Offset;
    }
    int maxoffset = Length;
    if ((Access & FILE_RIGHTS_WRITE) != 0) {
        maxoffset = MaxLength;
    }
    switch (origin) {
    case FILE_SEEK_CURRENT:
        Offset += position;
        break;
    case FILE_SEEK_START:
        Offset = 0 + position;
        break;
    case FILE_SEEK_END:
        Offset = maxoffset + position;
        break;
    }
    if (Offset < 0) {
        Offset = 0;
    }
    if (Offset > maxoffset) {
        Offset = maxoffset;
    }
    if (Offset > Length) {
        Length = Offset;
    }
    return Offset;
}
