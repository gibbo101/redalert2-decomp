// bool AITriggerTypeClass::Enemy_Power_Below_100(HouseClass *house, HouseClass *enemy) const (0x0041D290)
// The enemy's power surplus (output minus drain) is below 100 (a condition the trigger check 0x0041C990 expands in place).
#include "shared/ai_trigger_type.hpp"
#include "shared/house.hpp"
// @ref __real@8@4005c800000000000000=0079b7f0

bool AITriggerTypeClass::Enemy_Power_Below_100(HouseClass *house, HouseClass *enemy) const
{
    bool result = false;
    if (enemy != 0) {
        result = enemy->Power_Output() - enemy->Power_Drain() < 100.0;
    }
    return result;
}
