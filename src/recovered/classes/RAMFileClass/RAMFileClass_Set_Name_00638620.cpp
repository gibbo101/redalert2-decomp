// char const *RAMFileClass::Set_Name(char const *filename) (0x00638620, slot 2): the name is ignored.
#include "shared/ram_file_class.hpp"

char const *RAMFileClass::Set_Name(char const *)
{
    return File_Name();
}
