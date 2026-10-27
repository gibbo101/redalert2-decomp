// CCFileClass::Is_Available (0x004691A0, virtual slot 5)
// Available when open, when some mixfile holds it, or when it exists on disk.
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"

bool CCFileClass::Is_Available(int)
{
    if (Is_Open()) {
        return true;
    }
    if (MixFileClass<CCFileClass>::Offset(File_Name())) {
        return true;
    }
    return CDFileClass::Is_Available();
}
