// CCFileClass::Seek (0x004690F0, virtual slot 10)
// Moves the read position of a resident file, clamped to its size;
// otherwise seeks on disk.
#include "shared/cc_file_class.hpp"

long CCFileClass::Seek(long position, int origin)
{
    if (Data.Get_Buffer() != 0) {
        switch (origin) {
        case FILE_SEEK_START:
            Position = 0;
            break;
        case FILE_SEEK_END:
            Position = Data.Get_Size();
            break;
        }
        Position += position;
        Position = (Position < 0) ? 0 : Position;
        Position = (Position > Data.Get_Size()) ? Data.Get_Size() : Position;
        return Position;
    }
    return CDFileClass::Seek(position, origin);
}
