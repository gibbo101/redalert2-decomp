// ShipLocomotionClass::ShipLocomotionClass() (0x00675600)
// No ramps, a fresh slope timer, the destination and head-to coordinate at
// the unit's zero, no track (-1), unlocked (+0x65), no piggybacker.
#include "shared/ship_locomotion.hpp"
// @ref ??0LocomotionClass@@QAE@XZ=0053cfc0
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8
// @ref ??_7ShipLocomotionClass@@6BIPersistStream@@@=007ab204
// @ref ??_7ShipLocomotionClass@@6BILocomotion@@@=007ab13c
// @ref ??_7ShipLocomotionClass@@6B@=007ab118

ShipLocomotionClass::ShipLocomotionClass() :
    unknown_1c(0),
    unknown_20(0),
    unknown_34(unknown_coord_ab91c8),
    unknown_40(unknown_coord_ab91c8),
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
