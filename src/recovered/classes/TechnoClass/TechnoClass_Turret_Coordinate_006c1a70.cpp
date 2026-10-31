// Weapon mounting coordinate with the locomotor transform and turret angle.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/matrix3d.hpp"
// @ref _unknown_fire_angle_scale_79d090=0079d090
extern "C" double const unknown_fire_angle_scale_79d090;
CoordStruct TechnoClass::unknown_slot181(int which)
{
    TechnoTypeClass *type=unknown_slot32();
    Matrix3D matrix;
    double angle;
    FootClass *foot=this && unknown_14_bit2 ? static_cast<FootClass *>(this) : 0;
    if (foot && foot->Locomotor) {
        Matrix3D drawn;
        Matrix3D locomotor_matrix(*foot->Locomotor.Checked()->Draw_Matrix(&drawn,0));
        matrix=locomotor_matrix;
        angle=unknown_slot162().As_Radian32()-unknown_2e0.Current().As_Radian32();
    } else {
        matrix.Make_Identity();
        angle=unknown_slot162().As_Radian32();
    }
    matrix.Translate(type->TurretOffset,0.0f,0.0f);
    matrix.Rotate_Z((float)angle);
    Vector3 fire=matrix*Vector3(0.0f,0.0f,0.0f);
    CoordStruct offset((int)fire.X,(int)-fire.Y,(int)fire.Z);
    return offset+unknown_slot42();
}

// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
