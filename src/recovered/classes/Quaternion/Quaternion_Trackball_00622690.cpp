// Quaternion rotation between two positions projected onto a virtual trackball.
#include "shared/quaternion.hpp"
inline Vector3 operator-(Vector3 const &a, Vector3 const &b)
{
    return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

// The delta's length: the three doubles stay on the x87 stack in declaration order.
inline float Trackball_Length_00622690(Vector3 const &vector)
{
    double y = vector.Y;
    double z = vector.Z;
    double x = vector.X;
    return Fast_Sqrt(x * x + z * z + y * y);
}

static float project_to_sphere(float radius, float x, float y)
{
    const float sqrt_two = 1.41421356f;
    float distance = Fast_Sqrt(x * x + y * y);
    float z;
    if (distance < radius * (sqrt_two / 2.0f)) {
        z = Fast_Sqrt(radius * radius - distance * distance);
    } else {
        float tangent = radius / sqrt_two;
        z = tangent * tangent / distance;
    }
    return z;
}
Quaternion __fastcall Trackball(float x0, float y0, float x1, float y1, float radius)
{
    Vector3 axis;
    float angle;
    Vector3 first;
    Vector3 second;
    Vector3 delta;
    float distance;
    if (x0 == x1 && y0 == y1) return Quaternion(0.0f,0.0f,0.0f,1.0f);
    first.X = x0;
    first.Y = y0;
    first.Z = project_to_sphere(radius, x0, y0);
    second.X = x1;
    second.Y = y1;
    second.Z = project_to_sphere(radius, x1, y1);
    axis = Vector3::Cross_Product(second, first);
    delta = first - second;
    distance = Trackball_Length_00622690(delta) / (2.0 * radius);
    if (distance > 1.0f) distance = 1.0f;
    else if (distance < -1.0f) distance = -1.0f;
    // Existing accepted name for the original 004BA550 inverse-trig callee;
    // its asin/acos identity is still a separate hypothesis.
    angle = 2.0 * Fast_Acos(distance);
    return Axis_To_Quat(axis, angle);
}

// @ref ??0Vector3@@QAE@MMM@Z=00437690
// @ref __real@4@3ffeb504f30000000000=007a8658
// @ref __real@4@3ffeb504f367f3bcd800=007a8654
// @ref __real@4@bfff8000000000000000=007a8650
