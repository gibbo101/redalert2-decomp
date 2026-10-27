// bool FootClass::unknown_slot202() (0x004CD080)
// Whether the timer at +0x58C is still running.
#include "shared/foot.hpp"

bool FootClass::unknown_slot202()
{
    return unknown_58c.Value() != 0;
}
