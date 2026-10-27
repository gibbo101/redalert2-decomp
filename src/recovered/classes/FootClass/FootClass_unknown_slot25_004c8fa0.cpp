// int FootClass::unknown_slot25(bool arg1, int arg2) (0x004C8FA0)
// The locomotor's visual character (ILocomotion::Visual_Character) when it
// has one, else TechnoClass's.
#include "shared/foot.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_slot25@TechnoClass@@UAEH_NH@Z=006cf3c0

int FootClass::unknown_slot25(bool arg1, int arg2)
{
    if (Locomotor) {
        int result = Locomotor.Checked()->Visual_Character(arg1);
        if (result != 0) {
            return result;
        }
    }
    return TechnoClass::unknown_slot25(arg1, arg2);
}
