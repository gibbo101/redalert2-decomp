// JumpjetLocomotionClass::JumpjetLocomotionClass() (0x0052F160)
// The facing turns at the rules' jumpjet turn rate and starts at 0x4000.
#include "shared/jumpjet_locomotion.hpp"
#include "shared/rules.hpp"
// @ref ??0LocomotionClass@@QAE@XZ=0053cfc0
// @ref ??0FacingClass@@QAE@H@Z=004b89f0
// @ref ?Set_Desired@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8a30
// @ref ?Set_Current@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8b10
// @ref ?unknown_coord_a6e3e0@@3UCoordStruct@@A=00a6e3e0
// @ref ??_7JumpjetLocomotionClass@@6BIPersistStream@@@=007a536c
// @ref ??_7JumpjetLocomotionClass@@6BILocomotion@@@=007a52a4

JumpjetLocomotionClass::JumpjetLocomotionClass() :
    unknown_3c(unknown_coord_a6e3e0),
    unknown_48(false),
    unknown_4c(0),
    unknown_50(Rules->unknown_368),
    unknown_68(0),
    unknown_70(0),
    unknown_78(0),
    unknown_80(0),
    unknown_88(false)
{
    unknown_50.Set_Desired(UnknownFacingDir(0x4000));
    unknown_50.Set_Current(UnknownFacingDir(0x4000));
}
