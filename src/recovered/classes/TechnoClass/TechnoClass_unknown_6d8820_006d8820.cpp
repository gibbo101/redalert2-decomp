// void TechnoClass::unknown_6d8820() (0x006D8820)
// Steps a ten-state sequence (+0x16C) on the +0x160 timer while slot 203
// holds (the +0x154 timer runs), else resets it to 0: states 1-5 and 7-9
// wait out delays of 6, 4, 20, 8, 16 / 6, 4, 20 frames; state 5 returns to
// 4 while the +0x154 timer has 54 or more frames left, state 6 waits until
// it is down to 30; then 10 (TechnoClass::AI; meaning unknown).
#include "shared/techno.hpp"
// @ref ?Value@?$CDTimerClass@VFrameTimerClass@@@@QBEJXZ=004a4d20

void TechnoClass::unknown_6d8820()
{
    if (unknown_slot203()) {
        switch (unknown_16c) {
        case 0:
            unknown_16c = 1;
            unknown_160 = CDTimerClass<FrameTimerClass>(6);
            break;
        case 1:
            if (unknown_160.Value() == 0) {
                unknown_16c = 2;
                unknown_160 = CDTimerClass<FrameTimerClass>(4);
            }
            break;
        case 2:
            if (unknown_160.Value() == 0) {
                unknown_16c = 3;
                unknown_160 = CDTimerClass<FrameTimerClass>(20);
            }
            break;
        case 3:
            if (unknown_160.Value() == 0) {
                unknown_16c = 4;
                unknown_160 = CDTimerClass<FrameTimerClass>(8);
            }
            break;
        case 4:
            if (unknown_160.Value() == 0) {
                unknown_16c = 5;
                unknown_160 = CDTimerClass<FrameTimerClass>(16);
            }
            break;
        case 5:
            if (unknown_160.Value() == 0) {
                if (unknown_154 < 54) {
                    unknown_16c = 6;
                } else {
                    unknown_16c = 4;
                    unknown_160 = CDTimerClass<FrameTimerClass>(8);
                }
            }
            break;
        case 6:
            if (unknown_154 <= 30) {
                unknown_16c = 7;
                unknown_160 = CDTimerClass<FrameTimerClass>(6);
            }
            break;
        case 7:
            if (unknown_160.Value() == 0) {
                unknown_16c = 8;
                unknown_160 = CDTimerClass<FrameTimerClass>(4);
            }
            break;
        case 8:
            if (unknown_160.Value() == 0) {
                unknown_16c = 9;
                unknown_160 = CDTimerClass<FrameTimerClass>(20);
            }
            break;
        case 9:
            if (unknown_160.Value() != 0) {
                break;
            }
        default:
            unknown_16c = 10;
            break;
        }
    } else {
        unknown_16c = 0;
    }
}
