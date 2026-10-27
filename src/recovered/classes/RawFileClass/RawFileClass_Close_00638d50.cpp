// RawFileClass::Close (0x00638D50, virtual slot 13)
// Closes the handle if open. A failed CloseHandle is reported through Error()
// with the Win32 error code; the handle is invalidated either way.
#include "shared/raw_file_class.hpp"

void RawFileClass::Close()
{
    if (Is_Open()) {
        if (!CloseHandle(Handle)) {
            Error(GetLastError(), false, Filename);
        }
        Handle = INVALID_HANDLE_VALUE;
    }
}
