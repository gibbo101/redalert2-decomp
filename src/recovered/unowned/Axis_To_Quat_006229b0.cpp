// Quaternion rotation about a normalized axis.
#include "shared/quaternion.hpp"
// Vector3::Length, one call deep: Trackball inlines this row.
inline float Quat_Vector_Length(Vector3 const &vector)
{
    return Fast_Sqrt(vector.X * vector.X + vector.Y * vector.Y + vector.Z * vector.Z);
}
inline Vector3 Normalize(Vector3 const &vector)
{
    float length = Quat_Vector_Length(vector);
    if (length != 0.0) {
        double divisor = length;
        return Vector3((float)(vector.X / divisor), (float)(vector.Y / divisor), (float)(vector.Z / divisor));
    }
    return vector;
}
Quaternion __fastcall Axis_To_Quat(Vector3 const &axis, float angle)
{
    Quaternion result;
    Vector3 normalized = axis;
    normalized = Normalize(normalized);
    result.X = normalized.X;
    result.Y = normalized.Y;
    result.Z = normalized.Z;
    result.Scale(Fast_Sin(angle / 2.0f));
    result.W = Fast_Cos(angle / 2.0f);
    return result;
}

// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@4@3ffe8000000000000000=0079dd80
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
