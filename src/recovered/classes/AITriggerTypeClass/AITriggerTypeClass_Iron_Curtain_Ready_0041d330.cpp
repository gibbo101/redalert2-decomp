// bool AITriggerTypeClass::Iron_Curtain_Ready(HouseClass *house, HouseClass *enemy) const (0x0041D330)
// Whether the house's first super weapon of type 1 is present and has
// recharged far enough: the remaining fraction of its recharge time is at
// most 1 - the rules fraction (+0xB80).
#include "shared/ai_trigger_type.hpp"
#include "shared/house.hpp"
#include "shared/super.hpp"
#include "shared/super_weapon_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Frame@@3HA=00a40d2c
// @ref __real@4@3fff8000000000000000=0079b7f8

bool AITriggerTypeClass::Iron_Curtain_Ready(HouseClass *house, HouseClass *enemy) const
{
    if (house != 0) {
        for (int index = 0; index < house->Supers.Count(); index++) {
            if (house->Supers[index]->Type->Type == 1) {
                SuperClass *super = house->Supers[index];
                if (super != 0 && super->unknown_0x55) {
                    double remaining = super->RechargeTimer.Value();
                    double total = super->Type->RechargeTime;
                    if (remaining / total > 1.0f - Rules->unknown_b80) {
                        return false;
                    }
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}
