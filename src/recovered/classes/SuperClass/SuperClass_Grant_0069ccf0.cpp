// Grants this house a super weapon and applies its initial charging state.
// Existing AL-return/three-bool member contract retained, original0069CCF0.
#include "shared/super.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"

// @ref ?Start@?$CDTimerClass@VFrameTimerClass@@@@QAEXXZ=0069ed30
// @ref ??0?$CDTimerClass@VFrameTimerClass@@@@QAE@J@Z=00463f80
bool SuperClass::Grant(bool one_time, bool announce, bool on_hold)
{
    if (!unknown_0x55) {
        unknown_0x55 = true;
        unknown_0x56 = one_time;
        unknown_0x3C.unknown_0 = false;
        bool result = false;
        unknown_0x38 = Type->UIName;
        if (!one_time) Suspend(false);
        if (Type->ShowTimer && !House->Type->MultiplayPassive) {
            unknown_supers_a35db8.Add(this);
        }
        if (Type->ManualControl) {
            unknown_0x5C = -1;
            RechargeTimer = Type->RechargeTime;
            RechargeTimer.Stop();
        } else {
            result = Recharge(announce && !on_hold);
        }
        if (on_hold) Suspend(true);
        if (unknown_0x56) Forced_Charge(announce);
        return result;
    }
    return false;
}
