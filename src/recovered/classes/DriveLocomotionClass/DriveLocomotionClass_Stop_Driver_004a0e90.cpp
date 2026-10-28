// bool DriveLocomotionClass::Stop_Driver() (0x004A0E90)
// Clears the head-to coordinate (Westwood's DriveClass::Stop_Driver).
// Expanded where it is used; this out-of-line copy is never called.
#include "shared/drive_locomotion.hpp"
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998

bool DriveLocomotionClass::Stop_Driver()
{
    if (unknown_40 != unknown_coord_852998) {
        unknown_40 = unknown_coord_852998;
        unknown_63 = false;
        return true;
    }
    return false;
}
