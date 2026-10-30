// Matrix3D *DriveLocomotionClass::unknown_49faa0(Matrix3D *matrix) (0x0049FAA0)
// The slope tilt matrix: while a slope change runs, the blend from the old
// ramp (unknown_20) to the new one by Slope_Ratio; otherwise the new ramp's
// matrix, or identity when level. Draw_Matrix expands it; this copy is
// unreferenced.
#include "shared/drive_locomotion.hpp"
#include "shared/matrix3d.hpp"
// @ref ?Make_Identity@Matrix3D@@QAEXXZ=00590060
// @ref ?Unknown_00718D60@@YIPAVMatrix3D@@PAV1@H@Z=00718d60
// @ref ?Unknown_00718DF0@@YIPAVMatrix3D@@PAV1@HHN@Z=00718df0
// @ref __real@8@3fff8000000000000000=0079a708

Matrix3D *DriveLocomotionClass::unknown_49faa0(Matrix3D *matrix)
{
    Matrix3D tilt;
    tilt.Make_Identity();
    if (!unknown_24.Has_Completed2()) {
        Matrix3D blend;
        double ratio = Slope_Ratio();
        tilt = *Unknown_00718DF0(&blend, unknown_20, unknown_1c, ratio);
    } else if (unknown_1c != 0) {
        Matrix3D ramp;
        tilt = *Unknown_00718D60(&ramp, unknown_1c);
    }
    *matrix = tilt;
    return matrix;
}
