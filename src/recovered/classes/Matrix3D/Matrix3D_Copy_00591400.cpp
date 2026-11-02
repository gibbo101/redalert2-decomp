// 0x00591400: returns a copy of a Matrix3D (hidden return pointer in ecx, source
// in edx). Nothing in the executable calls or references it; written as a
// __fastcall free function by value like Matrix3D_Rigid_Inverse_00591420 (the
// ABI is a hypothesis). The copy constructor 0x0058FE10 defined earlier in
// matrix3d.cpp is expanded inline (rep movsd).
#include "shared/matrix3d.hpp"

Matrix3D __fastcall Matrix3D_Copy_00591400(Matrix3D const &matrix)
{
    return matrix;
}
