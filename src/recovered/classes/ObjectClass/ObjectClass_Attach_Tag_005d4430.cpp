// bool ObjectClass::Attach_Tag(TagClass *tag) (0x005D4430)
#include "shared/object_type.hpp"

bool ObjectClass::Attach_Tag(TagClass *tag)
{
    if (unknown_34 != 0) {
        unknown_34->unknown_2c--;
        unknown_34 = 0;
    }
    if (tag != 0) {
        unknown_34 = tag;
        tag->unknown_2c++;
        return true;
    }
    return false;
}
