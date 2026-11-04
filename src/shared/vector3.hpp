// Vector3: three floats (Westwood's Vector3; same layout and empty default
// constructor as the declaration in shared/particle.hpp, which should move
// here). The empty user-declared constructor is why global Vector3 objects
// get an empty dynamic initializer (0x00716EA0, 0x00716EB0).
#ifndef RA2_SHARED_VECTOR3_HPP
#define RA2_SHARED_VECTOR3_HPP

#ifdef VECTOR3_DECLARE_WWMATH
#include "shared/fast_math.hpp"
#endif

struct Vector3 {
    Vector3() {}
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
#ifdef RA2_BUILDING_VECTOR_NEGATE
    Vector3 operator-() const { return Vector3(-X, -Y, -Z); }
#endif

    Vector3 &Set_00437690(float x, float y, float z);
    Vector3 &Scale_004376b0(float factor);
    Vector3 &Add_004376e0(Vector3 const &other);
#ifdef RA2_VECTOR3_DECLARE_LENGTH
    float Length() const;                   // 0x00437710 (Westwood's (float)sqrt(Length2()); BounceClass::AI)
#endif

#ifdef VECTOR3_DECLARE_WWMATH
    // Westwood vector length helpers, inline in quat.cpp (Axis_To_Quat).
    float Length2() const { return X * X + Y * Y + Z * Z; }
    float Length() const { return Fast_Sqrt(Length2()); }
#endif
    static Vector3 Cross_Product(Vector3 const &a, Vector3 const &b)
    {
        return Vector3(a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X);
    }

    Vector3 &operator*=(float k)
    {
        X *= k;
        Y *= k;
        Z *= k;
        return *this;
    }
    float X;    // +0x00
    float Y;    // +0x04
    float Z;    // +0x08
};

#ifdef VECTOR3_DECLARE_WWMATH
// The divisor is double: retaining that width consumes the final x87 length
// operand in Axis_To_Quat's third division (0x006229B0).
inline Vector3 operator/(Vector3 const &vector, double divisor)
{
    return Vector3(vector.X / divisor, vector.Y / divisor, vector.Z / divisor);
}
#endif

inline Vector3 operator+(Vector3 const &a, Vector3 const &b)
{
    return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

inline Vector3 operator*(Vector3 const &vector, float scale)
{
    return Vector3(vector.X * scale, vector.Y * scale, vector.Z * scale);
}

#endif
