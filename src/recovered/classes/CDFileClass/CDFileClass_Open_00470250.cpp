// CDFileClass::Open(char const *, int) (0x00470250, virtual slot 8)
// Names the file and opens it. Reads search the directory list; writes
// (and disabled objects) use the name as given.
#include "shared/cd_file_class.hpp"

int CDFileClass::Open(char const *filename, int rights)
{
    BufferIOFileClass::Close();
    if (filename == 0) {
        Error(FILE_ERROR_NO_FILE_NAME, false, 0);
    }
    if (!IsDisabled && rights != FILE_RIGHTS_WRITE) {
        Set_Name(filename);
        return BufferIOFileClass::Open(rights);
    }
    BufferIOFileClass::Set_Name(filename);
    return BufferIOFileClass::Open(rights);
}
