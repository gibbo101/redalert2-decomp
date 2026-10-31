// Weapon mounting coordinate with the locomotor transform and turret angle.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/matrix3d.hpp"
// @ref _unknown_fire_angle_scale_79d090=0079d090
extern "C" double const unknown_fire_angle_scale_79d090;
inline unsigned UnknownFacingDir::Round_To_32() const
{
    return (((*(unsigned const *)this>>10)+1)>>1);
}
inline Dir32 UnknownFacingDir::As_Dir32() const
{
    return (Dir32)(Round_To_32()%32U);
}
inline double UnknownFacingDir::As_Radian32() const
{
    return (double)((As_Dir32()-8)*unknown_fire_angle_scale_79d090);
}
CoordStruct TechnoClass::unknown_slot43(int which)
{
    TechnoTypeClass *type=unknown_slot32();
    WeaponStruct *weapon=unknown_slot231(which);
    int fire_x=weapon->FLH.X;
    int fire_y=weapon->FLH.Y;
    int fire_z=weapon->FLH.Z;
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
    matrix.Translate((float)fire_x,(float)(fire_y*(unknown_310%2!=0 ? -1 : 1)),(float)fire_z);
    Vector3 fire=matrix*Vector3(0.0f,0.0f,0.0f);
    CoordStruct offset((int)fire.X,(int)-fire.Y,(int)fire.Z);
    return offset+unknown_slot42();
}

// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
