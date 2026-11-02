// CCFileClass::Get_Date_Time (0x00469350, virtual slot 14)
// A file inside a mixfile has the archive's modification time.
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"

unsigned long CCFileClass::Get_Date_Time()
{
    MixFileClass *mixfile = 0;
    unsigned long datetime = CDFileClass::Get_Date_Time();
    if (datetime == 0) {
        if (MixFileClass::Offset(File_Name(), 0, &mixfile, 0, 0)) {
            return CCFileClass(mixfile->Filename).Get_Date_Time();
        }
    }
    return datetime;
}
