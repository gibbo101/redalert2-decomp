// void Matrix3D::Look_At(Vector3 const &position, Vector3 const &target, float roll) (0x00590D50)
// A transform at position facing target: pitch and yaw from the direction,
// then roll about the view axis (Westwood's Look_At; the axis conventions
// follow the original calls).
#include "shared/matrix3d.hpp"
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?Rotate_Y@Matrix3D@@QAEXMM@Z=00590920
// @ref ?Rotate_X@Matrix3D@@QAEXMM@Z=00590800
// @ref ?Rotate_Z@Matrix3D@@QAEXM@Z=005909a0
// @ref __real@4@00000000000000000000=0079a738

double __cdecl unknown_sqrt_4ba410(double value);

void Matrix3D::Look_At(Vector3 const &position, Vector3 const &target, float roll)
{
    float dx = target.X - position.X;
    float dy = target.Y - position.Y;
    float dz = target.Z - position.Z;
    float len1 = (float)unknown_sqrt_4ba410(dy * dy + dx * dx + dz * dz);
    float len2 = (float)unknown_sqrt_4ba410(dx * dx + dz * dz);
    float sinp;
    float cosp;
    float siny;
    float cosy;
    if (len1 != 0.0f) {
        sinp = dy / len1;
        cosp = len2 / len1;
    } else {
        sinp = 0.0f;
        cosp = 1.0f;
    }
    if (len2 != 0.0f) {
        siny = dx / len2;
        cosy = dz / len2;
    } else {
        siny = 0.0f;
        cosy = 1.0f;
    }
    Make_Identity();
    Translate(position);
    Rotate_Y(siny, cosy);
    Rotate_X(-sinp, cosp);
    Rotate_Z(roll);
}
