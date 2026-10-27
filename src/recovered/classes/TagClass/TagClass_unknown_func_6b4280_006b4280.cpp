// bool TagClass::unknown_func_6b4280() const (0x006B4280)
// True when no other tag has the same type.
#include "shared/object.hpp"

bool TagClass::unknown_func_6b4280() const
{
    for (int index = 0; index < unknown_TagClass_list_00abfe48.Count(); index++) {
        TagClass *tag = unknown_TagClass_list_00abfe48[index];
        if (tag != this && tag->Class == Class) {
            return false;
        }
    }
    return true;
}
