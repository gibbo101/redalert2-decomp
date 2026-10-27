// void TagClass::Clear_All() (0x006B3FA0)
// Deletes every tag (each destructor removes it from Tags).
#include "shared/object.hpp"

void TagClass::Clear_All()
{
    while (unknown_TagClass_list_00abfe48.Count() > 0) {
        delete unknown_TagClass_list_00abfe48[0];
    }
}
