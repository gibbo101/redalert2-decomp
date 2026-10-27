// FileClass::Set_Date_Time (0x006386C0, virtual slot 15)
// Default: setting the time is unsupported.
#include "shared/raw_file_class.hpp"

bool FileClass::Set_Date_Time(unsigned long)
{
    return false;
}
