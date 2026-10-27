// bool FootClass::unknown_4c8d60() (0x004C8D60)
// Whether the mission (slot 91) is 7.
#include "shared/foot.hpp"

bool FootClass::unknown_4c8d60()
{
    return unknown_slot91() == 7 ? true : false;
}
