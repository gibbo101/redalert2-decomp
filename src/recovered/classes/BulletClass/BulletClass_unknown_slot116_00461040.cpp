// int BulletClass::unknown_slot116() (0x00461040)
// The shape frame: by the velocity's heading (one of 32 facings), or the
// animation frame for animated types.
#include "shared/bullet.hpp"

int BulletClass::unknown_slot116()
{
    int frame = 0;
    if (!Type_View(Type)->unknown_271) {
        UnknownDirStruct dir((unsigned short)((unknown_math_4ba600(-Velocity.Y, Velocity.X) - 1.5707963267948966) * -10430.060040584269));
        frame = unknown_facing_frames_7acab0[Dir_Facing32(dir)];
    }
    if (Type_View(Type)->unknown_2c4 || Type_View(Type)->unknown_2c5) {
        frame = AnimFrame;
    }
    return frame;
}
