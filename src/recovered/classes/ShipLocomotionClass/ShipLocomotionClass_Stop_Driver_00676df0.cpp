// bool ShipLocomotionClass::Stop_Driver() (0x00676DF0)
// Clears the head-to coordinate (Westwood's DriveClass::Stop_Driver).
// Expanded where it is used; this out-of-line copy is never called.
#include "shared/ship_locomotion.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8

bool ShipLocomotionClass::Stop_Driver()
{
    if (unknown_40 != unknown_coord_ab91c8) {
        unknown_40 = unknown_coord_ab91c8;
        unknown_63 = false;
        return true;
    }
    return false;
}
