// RawFileClass::Is_Open (0x006394D0, virtual slot 6)
// A file is open while it holds a valid Win32 handle.
#include "shared/raw_file_class.hpp"

bool RawFileClass::Is_Open() const
{
    return Handle != INVALID_HANDLE_VALUE;
}
