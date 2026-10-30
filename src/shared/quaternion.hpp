// Quaternion: X, Y, Z, W floats (Westwood's wwmath Quaternion; methods in
// quat.cpp from 0x00622160). shared/bounce.hpp's UnknownQuaternion
// (constructor 0x00622160) is this class (proposal: rename it).
#ifndef RA2_SHARED_QUATERNION_HPP
#define RA2_SHARED_QUATERNION_HPP

#include "shared/matrix3d.hpp"

class Quaternion {
public:
    Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);    // 0x00622160
    void Set(float x, float y, float z, float w);           // 0x00622180
    void Normalize();                                       // 0x006221A0 (divides by the squared length)
    void Scale(float scale);                                // 0x00622200
    float &operator[](int index);                           // 0x00622230
    float operator[](int index) const;                      // 0x00622240
    Quaternion operator=(Quaternion const &quat);           // 0x00622250
    Quaternion &Make_Closest(Quaternion const &target);     // 0x00622290

    float X;    // +0x00
    float Y;    // +0x04
    float Z;    // +0x08
    float W;    // +0x0C
};

Quaternion __fastcall operator*(Quaternion const &a, Quaternion const &b);     // 0x00622400
Quaternion __fastcall operator/(Quaternion const &a, Quaternion const &b);     // 0x00622570
Quaternion __fastcall Conjugate(Quaternion const &quat);                       // 0x006225F0
Quaternion __fastcall Inverse(Quaternion const &quat);                         // 0x00622640
Quaternion __fastcall Axis_To_Quat(Vector3 const &axis, float angle);          // 0x006229B0
Quaternion __fastcall Slerp(Quaternion const &a, Quaternion const &b, float alpha);    // 0x00622AC0
Matrix3D __fastcall Build_Matrix3D(Quaternion const &quat);                     // 0x00622EB0

#endif
