// FileStraw::Get (0x007738A0, virtual slot 2)
// Reads from the file, opening it for reading first if it is closed (and
// remembering to close it later). Returns the bytes read, 0 on failure.
#include "shared/file_straw.hpp"

int FileStraw::Get(void *buffer, int length)
{
    if (Valid_File() && buffer && length > 0) {
        if (!File->Is_Open()) {
            HasOpened = true;
            if (!File->Is_Available()) {
                return 0;
            }
            if (!File->Open(FILE_RIGHTS_READ)) {
                return 0;
            }
        }
        return File->Read(buffer, length);
    }
    return 0;
}
