// Random launch velocity from the original 00436C70..00436DB4.
#include "shared/bounce.hpp"
#include "shared/id_source.hpp"
extern "C" double const bounce_random_scale;
// @ref _bounce_random_scale=0079c280
extern "C" double const bounce_launch_scale;
// @ref _bounce_launch_scale=0079ca88
extern "C" double const bounce_full_circle;
// @ref _bounce_full_circle=0079c9b8
extern "C" double const bounce_elevation_base;
// @ref _bounce_elevation_base=0079a708
extern "C" double const bounce_elevation_scale;
// @ref _bounce_elevation_scale=0079ca80
inline double Bounce_Random_Double(double minimum, double maximum)
{
 return minimum+(maximum-minimum)*((double)Random_Pick(0,0x7ffffffe)*bounce_random_scale);
}
void BounceClass::Init(CoordStruct const &coord, double elasticity, double unused, double min_speed, double max_speed)
{
 Vector3 velocity;
 double speed=Bounce_Random_Double(min_speed,max_speed)*bounce_launch_scale;
 double yaw=Bounce_Random_Double(0.0,1.0)*bounce_full_circle;
 double pitch=Bounce_Random_Double(1.0,2.0)*bounce_elevation_scale;
 double cosine=unknown_cos_4ba4d0(pitch);
 velocity.X=cosine*unknown_cos_4ba4d0(yaw)*speed;
 velocity.Y=(unknown_cos_4ba4d0(pitch)*unknown_sin_4ba480(yaw)*speed);
 velocity.Z=unknown_sin_4ba480(pitch)*speed;
 Init(coord,elasticity,3.0,0.0,velocity,0.0);
}
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
