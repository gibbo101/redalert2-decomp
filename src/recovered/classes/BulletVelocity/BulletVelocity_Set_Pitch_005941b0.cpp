// @ref __real@8@40008000000000000000=0079a6f8
// @ref __real@8@40078000000000000000=0079a700
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@4004b400000000000000=0079a710
// @ref __real@8@4004f000000000000000=0079a718
// @ref __real@8@4005b400000000000000=0079a720
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@3ff78000000000000000=0079a730
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@bff1c9116cc4faf2b800=0079b620
// @ref __real@8@c00ca2f83d7b47677800=0079b628
// @ref __real@8@3fffc90fdaa22168c000=0079b630
#define RA2_DIR_MISSILE_ANGLES
#define RA2_BULLET_MISSILE_VELOCITY
#define RA2_BULLET_MISSILE_SET_PITCH_SOURCE
#include "shared/bullet_velocity.hpp"
// @ref ?Speed@BulletVelocityXY@@QBENXZ=0041b750
// @ref ?Speed@BulletVelocity@@QBENXZ=0041b7c0
// @ref ?Get_Pitch@BulletVelocity@@QBE?AVDirType@@XZ=0041b6e0

void BulletVelocity::Set_Pitch(DirType const &pitch)
{
    double current_pitch = Get_Pitch().As_Radian();
    double speed = Speed();
    if (current_pitch != 0) {
        X /= Fast_Cos(current_pitch);
        Y /= Fast_Cos(current_pitch);
    }
    X *= Fast_Cos(pitch.As_Radian());
    Y *= Fast_Cos(pitch.As_Radian());
    Z = speed * Fast_Sin(pitch.As_Radian());
}
