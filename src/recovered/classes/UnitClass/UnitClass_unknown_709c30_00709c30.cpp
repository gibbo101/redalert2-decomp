// void UnitClass::unknown_709c30(ObjectTypeClass *type) (0x00709C30)
// Starts a disguise (hypothesis): a given type becomes the shown type (+0x40C)
// with no house (+0x410), the flag at +0x170 is set, the frame is stamped at
// +0x174 and slot 266 reacts.
#include "shared/unit.hpp"
// @ref ?Frame@@3HA=00a40d2c

void UnitClass::unknown_709c30(ObjectTypeClass *type)
{
    if (type) {
        unknown_40c = type;
        unknown_410 = 0;
        unknown_170 = true;
        unknown_174 = Frame;
        unknown_slot266();
    }
}
