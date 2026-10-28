// Matrix3D * __stdcall RocketLocomotionClass::Draw_Matrix(Matrix3D *matrix, int *key) (0x0063EC00, ILocomotion 9)
// Turned by the facing and pitched (about Y) by +0x50; the key marks the
// rules' initial (0x20) or final (0x40) pitch of the rocket kind (V3Rocket
// for its type, else DMisl) and is -1 between them.
#include "shared/rocket_locomotion.hpp"
#include "shared/matrix3d.hpp"
#include "shared/aircraft.hpp"
#include "shared/rules.hpp"
// @ref __real@8@bffcc90fdaa22168c000=0079d090
// @ref __real@4@00000000000000000000=0079a738
// @ref __real@8@3fffc90fdaa22168c000=0079b630
// @ref ?Make_Identity@Matrix3D@@QAEXXZ=00590060
// @ref ?Rotate_Z@Matrix3D@@QAEXM@Z=005909a0
// @ref ?Rotate_Y@Matrix3D@@QAEXM@Z=00590880
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0

Matrix3D * __stdcall RocketLocomotionClass::Draw_Matrix(Matrix3D *matrix, int *key)
{
    Matrix3D transform;
    transform.Make_Identity();
    transform.Rotate_Z((float)((Dir_To_32(LinkedTo->unknown_2e0.Current()) - 8) * -0.19634954084936207));
    if (unknown_50 != 0.0f) {
        transform.Rotate_Y(-unknown_50);
        RocketStruct const *rocket;
        if (((AircraftClass *)LinkedTo)->Type == Rules->V3Rocket.Type) {
            rocket = &Rules->V3Rocket;
        } else {
            rocket = &Rules->DMisl;
        }
        float final_pitch = rocket->PitchFinal * 1.5707963267948966;
        if (key != 0) {
            if ((float)(rocket->PitchInitial * 1.5707963267948966) == unknown_50) {
                *key |= 0x20;
            } else if (unknown_50 == final_pitch) {
                *key |= 0x40;
            } else {
                *key = -1;
            }
        }
    }
    if (key != 0) {
        *key |= Dir_To_32(LinkedTo->unknown_2e0.Current());
    }
    *matrix = transform;
    return matrix;
}
