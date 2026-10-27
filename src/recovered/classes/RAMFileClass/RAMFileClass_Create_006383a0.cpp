// int RAMFileClass::Create() (0x006383A0, slot 3): empties a closed file.
#include "shared/ram_file_class.hpp"

int RAMFileClass::Create()
{
    if (!Is_Open()) {
        Length = 0;
        return true;
    }
    return false;
}
