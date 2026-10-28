// Matrix3D * __stdcall FlyLocomotionClass::Draw_Matrix(Matrix3D *matrix, int *key) (0x004BED90, ILocomotion 9)
// Turned by the second facing (+0x2F8; the key gains it as bits 3..7). In
// the air, a crashing aircraft (+0x37D) rolls and pitches by its own angles
// (+0x280/+0x284; key -1); one faster than its type's PitchSpeed pitches by
// PitchAngle (key bit 2) and rolls by RollAngle while turning (bits 0 and 1).
#include "shared/fly_locomotion.hpp"
#include "shared/matrix3d.hpp"
// @ref __real@8@bffcc90fdaa22168c000=0079d090
// @ref __real@8@00000000000000000000=0079b610
// @ref ?Make_Identity@Matrix3D@@QAEXXZ=00590060
// @ref ?Rotate_Z@Matrix3D@@QAEXM@Z=005909a0
// @ref ?Rotate_Y@Matrix3D@@QAEXM@Z=00590880
// @ref ?Rotate_X@Matrix3D@@QAEXM@Z=00590760
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Is_Turning_Positive@FacingClass@@QBEDXZ=004b8cc0
// @ref ?Is_Turning_Negative@FacingClass@@QBEDXZ=004b8d00

Matrix3D * __stdcall FlyLocomotionClass::Draw_Matrix(Matrix3D *matrix, int *key)
{
    Matrix3D transform;
    transform.Make_Identity();
    if (key != 0) {
        *key |= Dir_To_32(LinkedTo->unknown_2f8.Current()) << 3;
    }
    transform.Rotate_Z((float)((Dir_To_32(LinkedTo->unknown_2f8.Current()) - 8) * -0.19634954084936207));
    if (LinkedTo->unknown_slot108() > 0) {
        if (LinkedTo->unknown_37d) {
            transform.Rotate_X(LinkedTo->unknown_280);
            if (unknown_48 > LinkedTo->unknown_slot32()->PitchSpeed) {
                transform.Rotate_Y((float)(LinkedTo->unknown_284 + LinkedTo->unknown_slot32()->PitchAngle));
            } else {
                transform.Rotate_Y(LinkedTo->unknown_284);
            }
            if (key != 0) {
                *key = -1;
            }
        } else if (unknown_48 > LinkedTo->unknown_slot32()->PitchSpeed) {
            if (LinkedTo->unknown_slot32()->PitchAngle != 0.0) {
                if (key != 0) {
                    *key |= 4;
                }
                transform.Rotate_Y((float)LinkedTo->unknown_slot32()->PitchAngle);
            }
            if (LinkedTo->unknown_slot32()->RollAngle != 0.0) {
                if (LinkedTo->unknown_2f8.Is_Turning_Positive()) {
                    if (key != 0) {
                        *key |= 1;
                    }
                    transform.Rotate_X((float)LinkedTo->unknown_slot32()->RollAngle);
                } else if (LinkedTo->unknown_2f8.Is_Turning_Negative()) {
                    if (key != 0) {
                        *key |= 2;
                    }
                    transform.Rotate_X((float)-LinkedTo->unknown_slot32()->RollAngle);
                }
            }
        }
    }
    *matrix = transform;
    return matrix;
}
