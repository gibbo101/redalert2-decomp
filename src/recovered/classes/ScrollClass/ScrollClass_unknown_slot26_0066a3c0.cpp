// bool ScrollClass::unknown_slot26() (0x0066A3C0, slot 26)
// True while a drag select runs, when 0x00A40D44 is set, or when the
// tactical view's +0xD8 value is not 0.
#include "shared/scroll.hpp"
// @ref ?unknown_flag_a40d44@@3_NA=00a40d44
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref __real@4@00000000000000000000=0079a738

bool ScrollClass::unknown_slot26()
{
    if (unknown_4f2a || unknown_flag_a40d44) {
        return true;
    }
    if (unknown_tactical_83996c != 0 && unknown_tactical_83996c->unknown_d8 != 0.0f) {
        return true;
    }
    return false;
}
