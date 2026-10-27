// void __stdcall DriveLocomotionClass::Mark_All_Occupation_Bits(int mark) (0x004A4890, ILocomotion 39)
// Marks the cells toward the head-to coordinate when one is set.
#include "shared/drive_locomotion.hpp"
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998
// @ref ?unknown_4a0bc0@DriveLocomotionClass@@QAEXABUCoordStruct@@H@Z=004a0bc0

void __stdcall DriveLocomotionClass::Mark_All_Occupation_Bits(int mark)
{
    if (unknown_40 != unknown_coord_852998) {
        unknown_4a0bc0(unknown_40, mark);
    }
}
