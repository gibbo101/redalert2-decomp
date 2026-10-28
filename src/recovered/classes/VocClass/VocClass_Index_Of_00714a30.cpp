// int VocClass::Index_Of(VocClass *voc) (0x00714A30): the index of a VocClass
// in the unit's list, -1 for none.
#include "shared/voc_class.hpp"

int __fastcall VocClass::Index_Of(VocClass *voc)
{
    for (int index = 0; index < unknown_VocClass_list_00ad0818.Count(); index++) {
        if (unknown_VocClass_list_00ad0818[index] == voc) {
            return index;
        }
    }
    return -1;
}
