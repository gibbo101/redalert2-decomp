// bool AITriggerTypeClass::Enemy_Power_Below_0(HouseClass *house, HouseClass *enemy) const (0x0041D2E0)
// Extent: the inventory splits it at 0x0041D31D; a linear sweep reaches the
// ret 8 at 0x0041D31E, followed by padding to 0x0041D330.
// The enemy's power surplus is negative (a condition the trigger check 0x0041C990 expands in place).
#include "shared/ai_trigger_type.hpp"
#include "shared/house.hpp"

bool AITriggerTypeClass::Enemy_Power_Below_0(HouseClass *house, HouseClass *enemy) const
{
    bool result = false;
    if (enemy != 0) {
        result = enemy->Power_Output() - enemy->Power_Drain() < 0.0;
    }
    return result;
}
