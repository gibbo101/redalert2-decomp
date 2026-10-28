// void TemporalClass::Just_Let_Go() (0x006E2710)
// Releases the target and recursively the links chained before and after this one.
#include "shared/temporal.hpp"
#include "shared/techno.hpp"

void TemporalClass::Just_Let_Go()
{
    Target->unknown_204 = false;
    Target->unknown_20c = 0;
    Target = 0;
    if (unknown_44 != 0) {
        if (unknown_44->unknown_40 == this) {
            unknown_44->unknown_40 = 0;
        }
        unknown_44->Just_Let_Go();
    }
    if (unknown_40 != 0) {
        if (unknown_40->unknown_44 == this) {
            unknown_40->unknown_44 = 0;
        }
        unknown_40->Just_Let_Go();
    }
    unknown_44 = 0;
    unknown_40 = 0;
    unknown_3c = 0;
    unknown_38 = 0;
}
