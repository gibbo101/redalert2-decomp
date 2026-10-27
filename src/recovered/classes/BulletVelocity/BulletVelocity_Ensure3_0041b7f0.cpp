// Original Aircraft.cpp velocity helper; free __fastcall versus member spelling is an ABI hypothesis.
// Caller415790 passes the current BulletVelocity at bullet+0xD0, same ECX receiver.
#include "shared/bullet.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Aircraft_Velocity_Zero_0079b610@@3NB=0079b610
extern double const Aircraft_Velocity_Zero_0079b610;
void __fastcall Ensure_Velocity3_0041B7F0(BulletVelocity *velocity)
{
    if (velocity->X == Aircraft_Velocity_Zero_0079b610 && velocity->Y == Aircraft_Velocity_Zero_0079b610 && velocity->Z == Aircraft_Velocity_Zero_0079b610) velocity->X = 100.0;
}
