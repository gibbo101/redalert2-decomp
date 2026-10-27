// bool InfantryClass::unknown_slot52() (0x00504F00, slot 52)
// Stops the locomotor's animation, resets the infantry state (+0x5D0 2,
// +0x5C3, Sequence 0) and continues with FootClass's slot 52.
#include "shared/infantry.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_slot52@FootClass@@UAE_NXZ=004c9bd0

bool InfantryClass::unknown_slot52()
{
    Locomotor.Checked()->Stop_Movement_Animation();
    unknown_5d0 = 2;
    unknown_5c3 = false;
    Sequence = 0;
    return FootClass::unknown_slot52();
}
