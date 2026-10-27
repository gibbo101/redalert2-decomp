// RawFileClass::Delete (0x00639240, virtual slot 4)
// Deletes the named file from disk. Fails without a name, when the file does
// not exist, or when DeleteFileA fails (reported through Error()).
#include "shared/raw_file_class.hpp"

int RawFileClass::Delete()
{
    Close();
    if (Filename == 0) {
        Error(FILE_ERROR_NO_FILE_NAME, false, 0);
        return false;
    }
    if (!Is_Available()) {
        return false;
    }
    if (!DeleteFileA(Filename)) {
        Error(GetLastError(), false, Filename);
        return false;
    }
    return true;
}
