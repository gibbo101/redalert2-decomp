// void UnknownTechnoBlock::unknown_6d8bc0() (0x006D8BC0)
// One frame: adds the step to the value; at the end of a state moves on
// (1: hold +0x0C frames, 2: fall to 0 over +0x08 frames, 3: idle).
#include "shared/techno.hpp"

void UnknownTechnoBlock::unknown_6d8bc0()
{
    if (unknown_18 != 0) {
        unknown_14 = unknown_10 + unknown_14;
        if (--unknown_1c <= 0) {
            switch (unknown_18) {
            case 1:
                unknown_18 = 2;
                unknown_1c = unknown_0c;
                unknown_10 = 0;
                if (unknown_0c > 1) {
                    break;
                }
            case 2:
                unknown_18 = 3;
                unknown_1c = unknown_08;
                if (unknown_1c < 1) {
                    unknown_1c = 1;
                }
                unknown_10 = -((float)unknown_00 / unknown_1c);
                break;
            case 3:
                unknown_18 = 0;
                unknown_14 = 0;
                break;
            }
        }
    }
}
