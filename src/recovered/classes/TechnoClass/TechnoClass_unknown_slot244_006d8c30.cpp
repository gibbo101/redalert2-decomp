// int TechnoClass::unknown_slot244(int flags) (0x006D8C30, slot 244)
// Adds blink flags (2, or 4 in the middle of a pulse) by the phase of the
// frame since +0x174, while the +0x184 timer is idle or the owner passes
// HouseClass 0x004F52B0.
#include "shared/techno.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0

int TechnoClass::unknown_slot244(int flags)
{
    int result = flags;
    if (unknown_184.Value() != 0 && !House->Unknown_004F52B0()) {
        return result;
    }
    int phase = (Frame - unknown_174 + 64) % 256;
    if (phase >= 64) {
        if (phase < 68) {
            result |= 2;
        } else if (phase < 76) {
            result |= 4;
        } else if (phase < 80) {
            result |= 2;
        } else if (phase >= 112) {
            if (phase < 116) {
                result |= 2;
            } else if (phase < 124) {
                result |= 4;
            } else if (phase < 128) {
                result |= 2;
            }
        }
    }
    return result;
}
