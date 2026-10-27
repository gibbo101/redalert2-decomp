// RawFileClass::Create (0x00639200, virtual slot 3)
// Creates (or truncates) the file by opening it for writing and closing it.
// With a bias window the position is reset to the window start first.
#include "shared/raw_file_class.hpp"

int RawFileClass::Create()
{
    Close();
    if (Open(FILE_RIGHTS_WRITE)) {
        if (BiasLength != -1) {
            Seek(0, FILE_SEEK_START);
        }
        Close();
        return true;
    }
    return false;
}
