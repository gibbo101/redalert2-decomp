// CCFileClass::Open(char const *, int) (0x00401980, virtual slot 8)
// Names the file, then opens it with the given rights.
#include "shared/cc_file_class.hpp"

int CCFileClass::Open(char const *filename, int rights)
{
    Set_Name(filename);
    return Open(rights);
}
