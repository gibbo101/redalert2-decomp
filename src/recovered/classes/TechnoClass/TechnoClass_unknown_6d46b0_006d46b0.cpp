// int TechnoClass::unknown_6d46b0(int mission) (0x006D46B0)
// Whether a mission is neither 5 nor 6 (hypothesis: neither Guard nor
// Sticky). Never called: inlined at every use; owner and parameter are
// hypotheses.
#include "shared/techno.hpp"

int TechnoClass::unknown_6d46b0(int mission)
{
    if (mission != 5 && mission != 6) {
        return 1;
    }
    return 0;
}
