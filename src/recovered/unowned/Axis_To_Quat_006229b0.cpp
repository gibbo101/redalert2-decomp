// Quaternion rotation about a normalized axis.
#include "shared/quaternion.hpp"
inline Vector3 Normalize(Vector3 const &vector)
{
    float length = vector.Length();
    if (length != 0.0) return vector / length;
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
