// bool FootClass::unknown_slot290(CoordStruct &coord) (0x004C4B90)
// Sends the locomotor to a coordinate (ILocomotion::Move_To) and reports
// whether it is moving.
#include "shared/foot.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940

bool FootClass::unknown_slot290(CoordStruct &coord)
{
    CoordStruct to(coord.X, coord.Y, coord.Z);
    Locomotor.Checked()->Move_To(to);
    return Locomotor.Checked()->Is_Moving() != 0;
}
