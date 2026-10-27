// bool FootClass::unknown_slot291() (0x004C4B60)
// Stops the locomotor (ILocomotion::Stop_Moving); always false.
#include "shared/foot.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940

bool FootClass::unknown_slot291()
{
    Locomotor.Checked()->Stop_Moving();
    return false;
}
