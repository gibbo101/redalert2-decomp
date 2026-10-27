// ?Get_Current_Level@RadSiteClass@@QBEHXZ (0x006375D0)
// Level scaled by the time left.
#include "shared/radsite.hpp"

int RadSiteClass::Get_Current_Level() const
{
    if (RadDuration <= 0) {
        return 0;
    }
    return RadTimeLeft * RadLevel / RadDuration;
}
