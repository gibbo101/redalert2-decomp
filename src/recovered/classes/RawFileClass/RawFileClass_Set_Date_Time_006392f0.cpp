// RawFileClass::Set_Date_Time (0x006392F0, virtual slot 15)
// Sets the open file's last-access and last-write times from a packed DOS
// date (high word) and time (low word), keeping its creation time.
// Returns whether the time was set.
#include "shared/raw_file_class.hpp"

bool RawFileClass::Set_Date_Time(unsigned long datetime)
{
    if (Handle != INVALID_HANDLE_VALUE) {
        BY_HANDLE_FILE_INFORMATION info;
        if (GetFileInformationByHandle(Handle, &info)) {
            FILETIME time;
            if (DosDateTimeToFileTime((WORD)(datetime >> 16), (WORD)datetime, &time)) {
                return SetFileTime(Handle, &info.ftCreationTime, &time, &time) != 0;
            }
        }
    }
    return false;
}
