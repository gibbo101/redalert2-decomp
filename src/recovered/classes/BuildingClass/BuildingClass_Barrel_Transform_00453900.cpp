// Construct the voxel-barrel transform with the original ordered float stores.
#include "shared/building.hpp"
#include "shared/matrix3d.hpp"
// @ref __real@8@bffcc90fdaa22168c000=0079d090
// @ref ?Make_Identity@Matrix3D@@=00590060
// @ref ?Translate_X@Matrix3D@@=00590180
// @ref ?Translate_Y@Matrix3D@@=005901b0
// @ref ?Translate_Z@Matrix3D@@=005901e0
// @ref ?Rotate_Z@Matrix3D@@=005909a0
// @ref ?Rotate_Y@Matrix3D@@=00590880
// @ref ?Scale_X@Matrix3D@@=005902d0
// @ref ?Scale_Y@Matrix3D@@=005902f0
// @ref ?Scale_Z@Matrix3D@@=00590320
// @ref ?Current@FacingClass@@=004b8be0
inline double Barrel_Direction_Angle_00453900(UnknownFacingDir const &direction)
{
    int index=Dir_To_32(direction);
    index-=8;
    return (double)(index*-0.19634954084936207);
}
Matrix3D &BuildingClass::unknown_453900(Matrix3D &result)
{
    Matrix3D transform;
    transform.Make_Identity();
    transform.Translate_X((float)Type->VoxelBarrelOffsetToBuildingPivotPoint.X);
    transform.Translate_Y((float)Type->VoxelBarrelOffsetToBuildingPivotPoint.Y);
    transform.Translate_Z((float)Type->VoxelBarrelOffsetToBuildingPivotPoint.Z);
    transform.Rotate_Z((float)Barrel_Direction_Angle_00453900(unknown_2e0.Current()));
    transform.Translate_X((float)Type->VoxelBarrelOffsetToRotatePivotPoint.X);
    transform.Translate_Y((float)Type->VoxelBarrelOffsetToRotatePivotPoint.Y);
    transform.Translate_Z((float)Type->VoxelBarrelOffsetToRotatePivotPoint.Z);
    transform.Rotate_Y((float)(-Barrel_Direction_Angle_00453900(unknown_2c8.Current())));
    transform.Translate_X((float)Type->VoxelBarrelOffsetToPitchPivotPoint.X);
    transform.Translate_Y((float)Type->VoxelBarrelOffsetToPitchPivotPoint.Y);
    transform.Translate_Z((float)Type->VoxelBarrelOffsetToPitchPivotPoint.Z);
    float scale=(float)Type->unknown_13a8;
    transform.Scale_X(scale);
    transform.Scale_Y(scale);
    transform.Scale_Z(scale);
    return result=transform;
}
