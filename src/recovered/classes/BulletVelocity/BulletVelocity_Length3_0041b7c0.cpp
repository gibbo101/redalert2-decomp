// Original Aircraft.cpp velocity helper; free __fastcall versus member spelling is an ABI hypothesis.
// Caller415790 passes the current BulletVelocity at bullet+0xD0, same ECX receiver.
#include "shared/bullet.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Aircraft_Velocity_Zero_0079b610@@3NB=0079b610
extern double const Aircraft_Velocity_Zero_0079b610;
double __fastcall Velocity_Length3_0041B7C0(BulletVelocity const *velocity)
{
    double z = velocity->Z;
    double y = velocity->Y;
    double x = velocity->X;
    return unknown_sqrt_4ba410(x * x + y * y + z * z);
}
