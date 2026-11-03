// @ref __real@8@c00ca2f83d7b47677800=0079b628
// @ref __real@8@3fffc90fdaa22168c000=0079b630
#define RA2_DIR_MISSILE_ANGLES
#define RA2_BULLET_MISSILE_VELOCITY
#define RA2_BULLET_MISSILE_GET_PITCH_SOURCE
#include "shared/bullet_velocity.hpp"
// @ref ?Speed@BulletVelocityXY@@QBENXZ=0041b750

DirType BulletVelocity::Get_Pitch() const
{
    double const &horizontal = BulletVelocityXY::Speed();
    return Fast_Atan2(Z, horizontal);
}
