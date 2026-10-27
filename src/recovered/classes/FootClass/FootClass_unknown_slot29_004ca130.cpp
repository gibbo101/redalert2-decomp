// int FootClass::unknown_slot29() const (0x004CA130)
// The layer: the locomotor decides (ILocomotion::Layer).
#include "shared/foot.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940

int FootClass::unknown_slot29() const
{
    return Locomotor.Checked()->Layer();
}
