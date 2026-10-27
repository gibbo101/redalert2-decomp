// CCFileClass::Write (0x00469030, virtual slot 12)
// Files served from memory cannot be written (reported as EACCES).
#include "shared/cc_file_class.hpp"

long CCFileClass::Write(void const *buffer, long size)
{
    if (Data.Get_Buffer() != 0) {
        Error(FILE_ERROR_ACCESS, false, File_Name());
    }
    return CDFileClass::Write(buffer, size);
}
