// bool SuperClass::Recharge(bool player) (0x0069CFC0)
// Drops the animation and starts charging anew (player is unused).

bool SuperClass::Recharge(bool player)
{
    unknown_69ca70();
    if (Is_Present() && !unknown_0x57 && !unknown_0x58) {
        unknown_0x5C = -1;
        RechargeTimer.Start();
        RechargeTimer = Type->RechargeTime;
        if (Type->UseChargeDrain) {
            unknown_0x60 = 0;
        }
        return true;
    }
    return false;
}
