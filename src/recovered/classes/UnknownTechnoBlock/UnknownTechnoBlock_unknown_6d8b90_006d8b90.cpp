// void UnknownTechnoBlock::unknown_6d8b90() (0x006D8B90)
// Starts the rise: state 1 for +0x04 frames (at least one), stepping the value by
// amount / frames each frame.
#include "shared/techno.hpp"

void UnknownTechnoBlock::unknown_6d8b90()
{
    if (unknown_00 != 0) {
        unknown_18 = 1;
        unknown_1c = unknown_04;
        if (unknown_04 < 1) {
            unknown_1c = 1;
        }
        unknown_10 = (float)unknown_00 / unknown_1c;
    }
}
