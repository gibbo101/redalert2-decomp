// RawFileClass::Get_Date_Time (0x006392A0, virtual slot 14)
// Returns the last-write time of the open file packed as DOS date (high word)
// and DOS time (low word), or 0 when it cannot be read.
#include "shared/raw_file_class.hpp"

unsigned long RawFileClass::Get_Date_Time()
{
    BY_HANDLE_FILE_INFORMATION info;
    WORD date;
    WORD time;
    if (GetFileInformationByHandle(Handle, &info)) {
        FileTimeToDosDateTime(&info.ftLastWriteTime, &date, &time);
        return ((unsigned long)date << 16) | time;
    }
    return 0;
}
