// Matrix3D: a 3x4 affine transform of floats, rows of (x, y, z, translation)
// (Westwood's wwmath Matrix3D; methods in matrix3d.cpp, 0x0058FDE0-
// 0x005913F5). Layout from Make_Identity (0x00590060): 12 floats, row major.
//
// Member names follow Westwood's Matrix3D where the behaviour matches; the
// two fast trigonometric helpers (table lookups taking a double and
// returning a float) are named after what they compute.
#ifndef RA2_SHARED_MATRIX3D_HPP
#define RA2_SHARED_MATRIX3D_HPP

#include "shared/fast_math.hpp"
#include "shared/vector3.hpp"

#ifdef RA2_MATRIX3D_INLINE_COPY
struct Matrix3D_Data { float Data[12]; };
#endif

class Matrix3D {
public:
    Matrix3D() {}
    Matrix3D(float const *matrix);                                      // 0x0058FDE0
#ifdef RA2_MATRIX3D_INLINE_COPY
    // The copy constructor is an inline member-wise copy (0x0058FE10 is its
    // out-of-line copy; BounceClass 0x00436FC0 expands it).
    Matrix3D(Matrix3D const &matrix) { *(Matrix3D_Data *)Row = *(Matrix3D_Data const *)matrix.Row; }
#else
    Matrix3D(Matrix3D const &matrix);                                   // 0x0058FE10
#endif
    Matrix3D(float m11, float m12, float m13, float m14,
             float m21, float m22, float m23, float m24,
             float m31, float m32, float m33, float m34);                // 0x0058FE30
    Matrix3D(Vector3 const &x, Vector3 const &y, Vector3 const &z, Vector3 const &position);   // 0x0058FE90
    Matrix3D(float unknown1, float unknown2);                           // 0x0058FEF0
    Matrix3D(Vector3 const &axis, float angle);                         // 0x0058FF50
    // All twelve elements, row by row (WW3D's inline Matrix3D::Set; Tactical's constructor 0x006A24B0).
    void Set(float m11, float m12, float m13, float m14,
             float m21, float m22, float m23, float m24,
             float m31, float m32, float m33, float m34)
    {
        Row[0][0] = m11; Row[0][1] = m12; Row[0][2] = m13; Row[0][3] = m14;
        Row[1][0] = m21; Row[1][1] = m22; Row[1][2] = m23; Row[1][3] = m24;
        Row[2][0] = m31; Row[2][1] = m32; Row[2][2] = m33; Row[2][3] = m34;
    }

    void Make_Identity();                                               // 0x00590060
    void Translate(float x, float y, float z);                          // 0x00590090
    void Translate(Vector3 const &offset);                              // 0x005900F0
    void Translate_X(float x);                                          // 0x00590180
    void Translate_Y(float y);                                          // 0x005901B0
    void Translate_Z(float z);                                          // 0x005901E0
    void Scale(float scale);                                            // 0x00590210
    void Scale(float x, float y, float z);                              // 0x00590270
    void Scale_X(float x);                                              // 0x005902D0
    void Scale_Y(float y);                                              // 0x005902F0
    void Scale_Z(float z);                                              // 0x00590320
    void Shear_X(float y, float z);                                     // 0x00590350
    void Shear_Z(float x, float y);                                     // 0x005903A0
    void Shear_Y(float x, float z);                                     // 0x005903F0
    void Pre_Rotate_X(float theta);                                     // 0x00590440
    void Pre_Rotate_Y(float theta);                                     // 0x00590550
    void Pre_Rotate_Z(float theta);                                     // 0x00590650
    void Rotate_X(float theta);                                         // 0x00590760
    void Rotate_X(float s, float c);                                    // 0x00590800
    void Rotate_Y(float theta);                                         // 0x00590880
    void Rotate_Y(float s, float c);                                    // 0x00590920
    void Rotate_Z(float theta);                                         // 0x005909A0
    void Rotate_Z(float s, float c);                                    // 0x00590A40
    float Get_X_Translation() const;                                    // 0x00590AC0
    float Get_Y_Translation() const;                                    // 0x00590B10
    float Get_Z_Translation() const;                                    // 0x00590B60
    float Get_X_Rotation() const;                                       // 0x00590BB0
    float Get_Y_Rotation() const;                                       // 0x00590C10
    float Get_Z_Rotation() const;                                       // 0x00590C70
    Vector3 Rotate_Vector(Vector3 const &vector) const;                 // 0x00590CD0
    void Look_At(Vector3 const &position, Vector3 const &target, float roll);   // 0x00590D50
    void Obj_Look_At(Vector3 const &position, Vector3 const &target, float roll);   // 0x00590F10

    float Row[3][4];    // +0x00
};

// The matrix product (Tunnel and Hover Draw_Matrix, BulletClass::Draw_Voxel).
Matrix3D __fastcall operator*(Matrix3D const &left, Matrix3D const &right);   // 0x00591180

// The transformed point (rotation and translation). Defined last in
// matrix3d.cpp and called, not expanded, by the Get_* members.
Vector3 __fastcall operator*(Matrix3D const &matrix, Vector3 const &vector);   // 0x00591380

// Rigid affine inverse; hidden-return ABI evidenced by full-unit exact body. 0x00591420
Matrix3D __fastcall Matrix3D_Rigid_Inverse_00591420(Matrix3D const &matrix);

#endif
