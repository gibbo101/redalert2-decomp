// void TemporalClass::Let_Go() (0x006E2680)
// Releases the target and unchains the links before and after this one (each lets go too).
#include "shared/temporal.hpp"
#include "shared/techno.hpp"

void TemporalClass::Let_Go()
{
    if (Target != 0) {
        Target->unknown_204 = false;
        Target->unknown_20c = 0;
        Target = 0;
    }
    if (unknown_44 != 0) {
        if (unknown_44->unknown_40 == this) {
            unknown_44->unknown_40 = 0;
        }
        unknown_44->Just_Let_Go();
        unknown_44 = 0;
    }
    if (unknown_40 != 0) {
        if (unknown_40->unknown_44 == this) {
            unknown_40->unknown_44 = 0;
        }
        unknown_40->Just_Let_Go();
        unknown_40 = 0;
    }
    unknown_44 = 0;
    unknown_40 = 0;
    unknown_3c = 0;
    unknown_38 = 0;
}
