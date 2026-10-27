// int RAMFileClass::Open(int access) (0x00638410, slot 7)
// Opens the memory file from the start; opening for writing alone empties
// it. False without a buffer or when already open.
#include "shared/ram_file_class.hpp"

int RAMFileClass::Open(int access)
{
    if (Buffer == 0 || Is_Open()) {
        return false;
    }
    Offset = 0;
    Access = access;
    IsOpen = true;
    switch (access) {
    default:
    case FILE_RIGHTS_READ:
        break;
    case FILE_RIGHTS_WRITE:
        Length = 0;
        break;
    case FILE_RIGHTS_READ_WRITE:
        break;
    }
    return Is_Open();
}
