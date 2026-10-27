// int RAMFileClass::Delete() (0x006383C0, slot 4): empties a closed file.
#include "shared/ram_file_class.hpp"

int RAMFileClass::Delete()
{
    if (!Is_Open()) {
        Length = 0;
        return true;
    }
    return false;
}
