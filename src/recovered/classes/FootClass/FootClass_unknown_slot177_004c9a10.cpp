// int FootClass::unknown_slot177() (0x004C9A10)
// The locomotor's Z gradient (ILocomotion slot 15), 2 without a locomotor.
#include "shared/foot.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940

int FootClass::unknown_slot177()
{
    if (Locomotor) {
        return Locomotor.Checked()->Z_Gradient();
    }
    return 2;
}
