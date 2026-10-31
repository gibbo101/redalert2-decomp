// bool SuperClass::Suspend(bool on) (0x0069CC60)
// Puts the charging on hold or resumes it (TS SuperClass::Suspend without the charge-drain part).

bool SuperClass::Suspend(bool on)
{
    if (unknown_0x55 && !unknown_0x56 && on != unknown_0x58 && unknown_0x48) {
        if (!on && !Type->ManualControl) {
            RechargeTimer.Start();
        } else {
            RechargeTimer.Stop();
        }
        unknown_0x58 = on;
        return true;
    }
    return false;
}
