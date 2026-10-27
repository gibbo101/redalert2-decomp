// int TechnoClass::unknown_6d86f0(int value) (0x006D86F0)
// Scales value by a factor in 256ths chosen by the mode at +0x16C from the
// time left on the +0x160 timer, at most 2000; other modes leave it
// unchanged (BuildingClass slot 79). Body 304 bytes: code to 0x006D87F8
// and the nine-entry jump table at 0x006D87FC.
#include "shared/techno.hpp"

int TechnoClass::unknown_6d86f0(int value)
{
    int time = unknown_160.Value();
    int factor;
    switch (unknown_16c) {
    case 1:
        factor = ((12 - time) << 8) / 6;
        break;
    case 2:
    case 8:
        factor = 512;
        break;
    case 3:
        factor = (461 * time + 1020) / 20;
        break;
    case 4:
        factor = (1024 - 77 * time) / 8;
        break;
    case 5:
        factor = (77 * time + 816) / 16;
        break;
    case 6:
        factor = 51;
        break;
    case 7:
        factor = (3072 - 461 * time) / 6;
        break;
    case 9:
        factor = ((time + 20) << 8) / 20;
        break;
    default:
        return value;
    }
    value = (factor * value) >> 8;
    if (value > 2000) {
        value = 2000;
    }
    return value;
}
