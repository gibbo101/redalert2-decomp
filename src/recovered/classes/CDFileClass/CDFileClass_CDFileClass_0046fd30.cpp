// CDFileClass::CDFileClass(char const *) (0x0046FD30)
// A searching file; the name is resolved against the search list at once.
#include "shared/cd_file_class.hpp"

CDFileClass::CDFileClass(char const *filename) :
    IsDisabled(false)
{
    CDFileClass::Set_Name(filename);
}
