// RawFileClass::Raw_Seek (0x006393D0)
// Moves the Win32 file pointer, ignoring the bias window. Fails (reporting
// through Error()) when the file is not open or SetFilePointer fails.
#include "shared/raw_file_class.hpp"

long RawFileClass::Raw_Seek(long position, int origin)
{
    if (!Is_Open()) {
        Error(FILE_ERROR_NOT_OPEN, false, Filename);
        return 0;
    }
    switch (origin) {
    case FILE_SEEK_START:
        origin = FILE_BEGIN;
        break;
    case FILE_SEEK_CURRENT:
        origin = FILE_CURRENT;
        break;
    case FILE_SEEK_END:
        origin = FILE_END;
        break;
    }
    position = SetFilePointer(Handle, position, 0, origin);
    if (position == -1) {
        Error(GetLastError(), false, Filename);
        return 0;
    }
    return position;
}
