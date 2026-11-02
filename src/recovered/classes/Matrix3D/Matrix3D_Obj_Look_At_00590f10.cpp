// void Matrix3D::Obj_Look_At(Vector3 const &position, Vector3 const &target, float roll) (0x00590F10)
// A transform at position whose Z axis points at target (yaw and pitch from the direction, then roll),
// built from the forward, up and right vectors (Westwood's wwmath Obj_Look_At). The up vector is
// assigned member by member and the length is held as a double (both fix the original's load order).
#include "shared/matrix3d.hpp"
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref __real@4@00000000000000000000=0079a738
// @ref __real@8@00000000000000000000=0079b610

void Matrix3D::Obj_Look_At(Vector3 const &position, Vector3 const &target, float roll)
{
    Vector3 dir(target.X - position.X, target.Y - position.Y, target.Z - position.Z);
    float yaw;
    if (dir.Y == 0.0f && dir.X == 0.0f) {
        yaw = 0.0f;
    } else {
        yaw = Fast_Atan2(dir.Y, dir.X);
    }
    float pitch = Fast_Atan2(-dir.Z, Fast_Sqrt(dir.X * dir.X + (dir.Y * dir.Y)));
    float cy = Fast_Cos(yaw);
    float sy = Fast_Sin(yaw);
    float cp = Fast_Cos(pitch);
    float sp = Fast_Sin(pitch);
    float cr = Fast_Cos(roll);
    float sr = Fast_Sin(roll);
    Vector3 up;
    up.X = sr * sy + cr * sp * cy;
    up.Y = cr * sp * sy - sr * cy;
    up.Z = cr * cp;
    double len = Fast_Sqrt(dir.X * dir.X + dir.Y * dir.Y + dir.Z * dir.Z);
    Vector3 forward;
    if (len != 0.0) {
        forward = Vector3(dir.X / len, dir.Y / len, dir.Z / len);
    } else {
        forward = dir;
    }
    Vector3 right(forward.Y * up.Z - forward.Z * up.Y, forward.Z * up.X - forward.X * up.Z, up.Y * forward.X - up.X * forward.Y);
    Row[0][0] = right.X;
    Row[0][1] = up.X;
    Row[0][2] = forward.X;
    Row[0][3] = position.X;
    Row[1][0] = right.Y;
    Row[1][1] = up.Y;
    Row[1][2] = forward.Y;
    Row[1][3] = position.Y;
    Row[2][0] = right.Z;
    Row[2][1] = up.Z;
    Row[2][2] = forward.Z;
    Row[2][3] = position.Z;
}
