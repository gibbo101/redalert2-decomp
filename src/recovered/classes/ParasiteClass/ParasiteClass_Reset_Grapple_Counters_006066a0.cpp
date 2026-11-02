// Reset the two grapple counters (0x006066A0); existing 9-byte body.
#define PARASITE_DECLARATIONS_ONLY
#define PARASITE_GRAPPLE_COUNTERS
#include "shared/parasite.hpp"

void ParasiteClass::Reset_Grapple_Counters_006066a0()
{
    unknown_50 = 0;
    unknown_4c = 0;
}
