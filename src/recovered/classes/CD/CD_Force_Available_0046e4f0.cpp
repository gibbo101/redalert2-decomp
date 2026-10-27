// bool CD::Force_Available(int cd) (0x0046E4F0, slot 0)
// Makes sure the disk is available: nothing to do for -2 (any disk) or a
// local installation, else searches for it with the music theme reset.
// Assumes: the -2/IsLocal meanings and the callee's purpose (hypotheses).
#include "shared/cd.hpp"
// @ref ?IsLocal@CD@@2_NA=00850828
// @ref ?Unknown_004985C0@CD@@QAE_NH@Z=004985c0

bool CD::Force_Available(int cd)
{
    if (cd == -2) {
        return true;
    }
    if (IsLocal == true) {
        return true;
    }
    LastTheme = THEME_NONE;
    return Unknown_004985C0(cd);
}
