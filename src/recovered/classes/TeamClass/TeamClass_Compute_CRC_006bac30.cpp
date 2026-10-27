// void TeamClass::Compute_CRC(WWCRCEngine &crc) const (0x006BAC30)
#include "shared/team.hpp"
#include "shared/team_type.hpp"
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEJPBXH@Z=00493fc0

// CDTimerClass::Value() for the timer type whose class is not recovered.
inline long Timer_Value(UnknownTimer423F60 const &timer)
{
    long remain = timer.DelayTime;
    if (timer.Started != -1) {
        long value = timer.Timer - timer.Started;
        if (value < remain) {
            return remain - value;
        } else {
            return 0;
        }
    }
    return remain;
}

void TeamClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc(Class->Fetch_ID());
    crc(((AbstractClass *)Owner)->Fetch_ID());
    if (unknown_38 != 0) {
        crc(unknown_38->Fetch_ID());
    }
    crc((long)unknown_48);
    crc((long)unknown_4c);
    if (Member != 0) {
        crc(((AbstractClass *)Member)->Fetch_ID());
    }
    crc(unknown_58.Value());
    crc(Timer_Value(unknown_64));
    if (Tag != 0) {
        crc(((AbstractClass *)Tag)->Fetch_ID());
    }
    crc(IsForcedActive);
    crc(IsHasBeen);
    crc(IsFullStrength);
    crc(IsUnderStrength);
    crc(IsReforming);
    crc(IsLagging);
    crc(NeedsToDisappear);
    crc(JustDisappeared);
    crc(IsMoving);
    crc(StepCompleted);
    crc(TargetNotAssigned);
    crc(IsLeavingMap);
    crc(unknown_84, sizeof(unknown_84));
}
