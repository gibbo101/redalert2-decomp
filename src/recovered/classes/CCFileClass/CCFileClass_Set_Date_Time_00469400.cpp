// CCFileClass::Set_Date_Time (0x00469400, virtual slot 15)
// A file inside a mixfile sets the archive's modification time.
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"

bool CCFileClass::Set_Date_Time(unsigned long datetime)
{
    MixFileClass *mixfile = 0;
    bool result = CDFileClass::Set_Date_Time(datetime);
    if (!result) {
        if (MixFileClass::Offset(File_Name(), 0, &mixfile, 0, 0)) {
            return CCFileClass(mixfile->Filename).Set_Date_Time(datetime);
        }
    }
    return result;
}
