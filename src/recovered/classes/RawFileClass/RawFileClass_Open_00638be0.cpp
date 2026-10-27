// RawFileClass::Open(char const *, int) (0x00638BE0, virtual slot 8)
// Names the file, then opens it with the given rights.
#include "shared/raw_file_class.hpp"

int RawFileClass::Open(char const *filename, int rights)
{
    Set_Name(filename);
    return Open(rights);
}
