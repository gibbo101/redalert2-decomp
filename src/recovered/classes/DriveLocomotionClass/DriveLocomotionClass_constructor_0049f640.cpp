// DriveLocomotionClass::DriveLocomotionClass() (0x0049F640)
// No ramps, a fresh slope timer, the destination and head-to coordinate at
// the unit's zero, no track (-1), unlocked (+0x65), no piggybacker.
#include "shared/drive_locomotion.hpp"
// @ref ??0LocomotionClass@@QAE@XZ=0053cfc0
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998
// @ref ??_7DriveLocomotionClass@@6BIPersistStream@@@=007a0594
// @ref ??_7DriveLocomotionClass@@6BILocomotion@@@=007a04cc
// @ref ??_7DriveLocomotionClass@@6B@=007a04a8

DriveLocomotionClass::DriveLocomotionClass() :
    unknown_1c(0),
    unknown_20(0),
    unknown_34(unknown_coord_852998),
    unknown_40(unknown_coord_852998),
    unknown_4c(0),
    unknown_50(0),
    unknown_58(-1),
    unknown_5c(-1),
    unknown_60(false),
    unknown_61(false),
    unknown_62(false),
    unknown_63(false),
    unknown_64(false),
    unknown_65(true)
{
}
