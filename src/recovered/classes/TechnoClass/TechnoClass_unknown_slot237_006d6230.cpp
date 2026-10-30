// void TechnoClass::unknown_slot237() (0x006D6230)
// Tilt update: the pitch (+0x280) and roll (+0x284) angles follow their
// rates (+0x288, +0x28C), clamped to a quarter turn (a tenth of a turn of
// roll for a foot with +0x59F); the rates decay back towards level and
// an angle that crosses level stops there.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/facing.hpp"
// @ref __real@4@3ff683126f0000000000=007ad018
// @ref __real@4@3ffda0d97c0000000000=007ad00c
// @ref __real@4@3ffec90fdb0000000000=007a7d00
// @ref __real@4@bffec90fdb0000000000=007ad01c
// @ref __real@8@3fefa7c5ac471b478800=007a4628
// @ref __real@8@bfefa7c5ac471b478800=007ad020
// @ref __real@8@3ff7a3d70ac000000000=007ad010

void TechnoClass::unknown_slot237()
{
    bool pitch_up = unknown_280 > 0.00002;
    bool pitch_down = unknown_280 < -0.00002;
    if (unknown_325) {
        float roll = unknown_284 < 0.0f ? -unknown_284 : unknown_284;
        if (roll < 0.7853982f) {
            int facing = Dir_To_8(unknown_2e0.Current());
            if (facing != 0 && (facing <= 5 || facing > 7)) {
                unknown_284 += 0.01;
            } else {
                unknown_284 -= 0.01;
            }
        }
        return;
    }
    if (unknown_37d) {
        unknown_284 += unknown_28c;
        unknown_280 += unknown_288;
        return;
    }

    if (unknown_288 != 0.0f) {
        unknown_280 += unknown_288;
        if (unknown_280 > 0.7853982f) {
            unknown_280 = 0.7853982f;
            unknown_288 = 0.0f;
        } else if (unknown_280 < -0.7853982f) {
            unknown_280 = -0.7853982f;
            unknown_288 = 0.0f;
        }
        if (pitch_up) {
            if (unknown_288 > 0.0f) {
                unknown_288 -= 0.002f;
            } else {
                unknown_288 -= 0.002f * 2.5;
            }
        } else {
            if (unknown_288 < 0.0f) {
                unknown_288 += 0.002f;
            } else {
                unknown_288 += 0.002f * 2.5;
            }
        }
    } else {
        unknown_280 = 0.0f;
    }
    if ((pitch_up && unknown_280 < 0.00002) || (pitch_down && unknown_280 > -0.00002)) {
        unknown_288 = 0.0f;
        unknown_280 = 0.0f;
    }

    bool roll_up = unknown_284 > 0.00002;
    bool roll_down = unknown_284 < -0.00002;
    if (unknown_28c != 0.0f) {
        float roll = unknown_28c + unknown_284;
        unknown_284 = roll;
        float limit = 0.7853982f;
        bool foot;
        if (this != 0) foot = unknown_14_bit2;
        if (this != 0 && foot && ((FootClass *)this)->unknown_59f) {
            limit = 0.31415927f;
        }
        if (roll > limit) {
            unknown_284 = limit;
            unknown_28c = 0.0f;
        } else if (roll < -limit) {
            unknown_284 = -limit;
            unknown_28c = 0.0f;
        }
        if (roll_up) {
            if (unknown_28c > 0.0f) {
                unknown_28c -= 0.002f;
            } else {
                unknown_28c -= 0.002f * 2.5;
            }
        } else {
            if (unknown_28c < 0.0f) {
                unknown_28c += 0.002f;
            } else {
                unknown_28c += 0.002f * 2.5;
            }
        }
    } else {
        unknown_284 = 0.0f;
    }
    if ((roll_up && unknown_284 < 0.00002) || (roll_down && unknown_284 > -0.00002)) {
        unknown_28c = 0.0f;
        unknown_284 = 0.0f;
    }
}
