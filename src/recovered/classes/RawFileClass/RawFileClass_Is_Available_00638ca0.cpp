// RawFileClass::Is_Available (0x00638CA0, virtual slot 5)
// Reports whether the named file exists. An open file is available. Otherwise
// the file is probed: normally with a short-lived CreateFileA handle, or,
// when forced, by a full Open(READ) and Close().
#include "shared/raw_file_class.hpp"

bool RawFileClass::Is_Available(int forced)
{
    if (Filename == 0) {
        return false;
    }
    if (Is_Open()) {
        return true;
    }
    if (forced) {
        RawFileClass::Open(FILE_RIGHTS_READ);
        RawFileClass::Close();
        return true;
    }
    Handle = CreateFileA(Filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (Handle == INVALID_HANDLE_VALUE) {
        return false;
    }
    if (!CloseHandle(Handle)) {
        Error(GetLastError(), false, Filename);
    }
    Handle = INVALID_HANDLE_VALUE;
    return true;
}
