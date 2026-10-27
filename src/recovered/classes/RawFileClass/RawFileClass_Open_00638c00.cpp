// RawFileClass::Open(int) (0x00638C00, virtual slot 7)
// Opens the named file with the requested rights:
//   READ        existing file, shared read/write, sequential-scan hint
//   WRITE       create or truncate, exclusive
//   READ_WRITE  open or create, exclusive
// Any other rights value leaves the handle unchanged. An open bias window
// repositions to its start. Returns whether the file is now open.
#include "shared/raw_file_class.hpp"

int RawFileClass::Open(int rights)
{
    Close();
    if (Filename == 0) {
        Error(FILE_ERROR_NO_FILE_NAME, false, 0);
        return false;
    }
    Rights = rights;
    switch (rights) {
    case FILE_RIGHTS_READ:
        Handle = CreateFileA(Filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0);
        break;
    case FILE_RIGHTS_WRITE:
        Handle = CreateFileA(Filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        break;
    case FILE_RIGHTS_READ_WRITE:
        Handle = CreateFileA(Filename, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        break;
    }
    if (BiasStart != 0 || BiasLength != -1) {
        Seek(0, FILE_SEEK_START);
    }
    return Handle != INVALID_HANDLE_VALUE;
}
