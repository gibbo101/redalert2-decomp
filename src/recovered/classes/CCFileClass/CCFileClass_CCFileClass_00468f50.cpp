// CCFileClass::CCFileClass(char const *) (0x00468F50)
// A named file; the name is resolved against the search directories.
#include "shared/cc_file_class.hpp"

CCFileClass::CCFileClass(char const *filename) :
    Position(0)
{
    CDFileClass::Set_Name(filename);
}
