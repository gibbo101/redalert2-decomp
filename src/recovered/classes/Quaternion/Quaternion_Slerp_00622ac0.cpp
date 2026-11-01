// ?Slerp@@YI?AVQuaternion@@ABV1@0M@Z (0x00622AC0)
// Spherical interpolation from a to b by t.
#include "shared/quaternion.hpp"

#define SLERP_EPSILON 1e-5

Quaternion __fastcall Slerp(Quaternion const &a, Quaternion const &b, float t)
{
    Quaternion res;
    double alpha;
    double beta;
    double theta;
    double sin_t, cos_t;

    cos_t = a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;

    if ((cos_t + 1.0) > SLERP_EPSILON) {
        if ((1.0 - cos_t) > SLERP_EPSILON) {
            theta = Fast_Asin(cos_t);
            sin_t = Fast_Sin(theta);
            beta = Fast_Sin((1.0f - t) * theta) / sin_t;
            alpha = Fast_Sin(t * theta) / sin_t;
        } else {
            beta = 1.0f - t;
            alpha = t;
        }
        for (int i = 0; i < 4; i++) {
            res[i] = (beta * a[i]) + (alpha * b[i]);
        }
    } else {
        beta = Fast_Sin((1.0f - t) * (3.14159265358979 / 2));
        alpha = Fast_Sin(t * (3.14159265358979 / 2));
        for (int i = 0; i < 4; i++) {
            res[i] = (beta * a[i]) + (alpha * b[i]);
        }
    }
    return res;
}
// @ref ?Fast_Asin@@YAMN@Z=004ba580
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref __real@4@3fff8000000000000000=0079b7f8
// @ref __real@8@3feea7c5ac471b478800=0079c520
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@3fffc90fdaa221688800=007a8660
