// CCFileClass::Is_Open (0x004691E0, virtual slot 6)
// A resident file is always open.
#include "shared/cc_file_class.hpp"

bool CCFileClass::Is_Open() const
{
    if (Data.Get_Buffer() != 0) {
        return true;
    }
    return CDFileClass::Is_Open();
}
