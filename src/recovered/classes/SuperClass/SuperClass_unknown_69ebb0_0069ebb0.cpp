// void SuperClass::unknown_69ebb0() (0x0069EBB0)
// Drops the animation and restarts the recharge timer from the full recharge time.

void SuperClass::unknown_69ebb0()
{
    unknown_69ca70();
    unknown_0x57 = false;
    unknown_0x5C = -1;
    bool active = RechargeTimer.Is_Active();
    RechargeTimer = Type->RechargeTime;
    if (!active) {
        RechargeTimer.Stop();
    }
}
