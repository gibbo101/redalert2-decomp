// bool TActionClass::unknown_func_6b1e70(...) (0x006B1E70)
// Deletes every tag whose type is the one at +0x4C (the count is read
// once; the index steps back after each deletion); always true.
#include "shared/taction.hpp"
#include "shared/tag.hpp"

bool TActionClass::unknown_func_6b1e70(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_4c != 0) {
        int count = unknown_TagClass_list_00abfe48.Count();
        for (int index = 0; index < count; index++) {
            if (unknown_TagClass_list_00abfe48[index]->Class == (TagTypeClass *)unknown_4c) {
                delete unknown_TagClass_list_00abfe48[index];
                index--;
            }
        }
    }
    return true;
}


