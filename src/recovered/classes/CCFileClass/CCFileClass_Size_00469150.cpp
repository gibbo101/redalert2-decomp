// CCFileClass::Size (0x00469150, virtual slot 11)
// A resident file's size; for a file found only inside a mixfile, the member
// size; otherwise the disk size.
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"

long CCFileClass::Size()
{
    if (Data.Get_Buffer() != 0) {
        return Data.Get_Size();
    }
    if (!CDFileClass::Is_Available()) {
        long length = 0;
        MixFileClass<CCFileClass>::Offset(File_Name(), 0, 0, 0, &length);
        return length;
    }
    return CDFileClass::Size();
}
