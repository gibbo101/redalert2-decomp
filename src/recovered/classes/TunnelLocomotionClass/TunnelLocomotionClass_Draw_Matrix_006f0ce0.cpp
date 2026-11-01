// Matrix3D * __stdcall TunnelLocomotionClass::Draw_Matrix(Matrix3D *matrix, int *key) (0x006F0CE0, ILocomotion 9)
// Above ground (state 0): the base transform, tilted by the cell's slope
// matrix; the key gains the ramp. Otherwise the base transform pitched about
// Y by the state's dig angle (the key gains its 32nds; -1 while the angle
// changes). Each base result goes to a buffer that lives only as long as the
// original's by-value return temporary: a block local in the two branches, a
// temporary in the declaration that copies it on the dig path (the original's
// frame gives the three their own lifetimes; a function-scope buffer does not).
#include "shared/tunnel_locomotion.hpp"
#include "shared/cell.hpp"
// @ref ?Unknown_00718D60@@YIPAVMatrix3D@@PAV1@H@Z=00718d60
// @ref ??D@YI?AVMatrix3D@@ABV0@0@Z=00591180
// @ref ??0Matrix3D@@QAE@ABV0@@Z=0058fe10
// @ref ?Draw_Matrix@LocomotionClass@@UAGPAVMatrix3D@@PAV2@PAH@Z=0053d030
// @ref ?Make_Identity@Matrix3D@@QAEXXZ=00590060
// @ref ?Rotate_Y@Matrix3D@@QAEXM@Z=00590880
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@3fffc90fdaa22168c000=0079b630
// @ref __real@8@bfffc90fdaa22168c000=007a8fd0
// @ref __real@8@40048000000000000000=007adcb0

Matrix3D * __stdcall TunnelLocomotionClass::Draw_Matrix(Matrix3D *matrix, int *key)
{
    if (unknown_18 == 0) {
        CoordStruct coord = LinkedTo->Coord;
        int ramp = Map[coord].unknown_11c;
        if (key != 0 && *key != -1) {
            *key = (*key << 6) + ramp;
        }
        Matrix3D transform;
        transform.Make_Identity();
        if (ramp != 0) {
            Matrix3D temp;
            Matrix3D body(*LocomotionClass::Draw_Matrix(&temp, key));
            Matrix3D ramp_matrix;
            transform = *Unknown_00718D60(&ramp_matrix, ramp) * body;
        } else {
            Matrix3D temp;
            Matrix3D body(*LocomotionClass::Draw_Matrix(&temp, key));
            transform = body;
        }
        *matrix = transform;
        return matrix;
    }

    double angle;
    switch (unknown_18) {
    case 3:
        angle = 1.5707963267948966;
        break;
    case 5:
        angle = -1.5707963267948966;
        break;
    case 2:
        if (key != 0) {
            *key = -1;
        }
        angle = unknown_28.Ratio() * 1.5707963267948966;
        break;
    case 6:
        if (key != 0) {
            *key = -1;
        }
        angle = (1.0 - unknown_28.Ratio()) * -1.5707963267948966;
        break;
    case 7:
        if (key != 0) {
            *key = -1;
        }
        angle = (1.0 - unknown_28.Ratio()) * 1.5707963267948966;
        break;
    default:
        angle = 0;
        break;
    }
    Matrix3D transform(*LocomotionClass::Draw_Matrix(&Matrix3D(), key));
    if (key != 0 && *key != -1) {
        *key = (*key << 8) | ((int)(angle * 32.0) & 0x3F);
    }
    transform.Rotate_Y((float)angle);
    *matrix = transform;
    return matrix;
}
