// EventClass::EventClass(int house, TargetClass whom, unsigned char mission, TargetClass target, TargetClass destination, long formation_speed, long max_speed) (0x004B61F0): event type 5.
#include "shared/event.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BM@IDNF@Adding?5event?5MEGAMISSION_F?6?$AA@=007d68bc

EventClass::EventClass(int house, TargetClass whom, unsigned char mission, TargetClass target, TargetClass destination, long formation_speed, long max_speed)
{
    Debug_Printf("Adding event MEGAMISSION_F\n");
    if (house >= 0) {
        House = house;
        Type = 5;
        Data.MegaMissionF.Whom = whom;
        Data.MegaMissionF.Mission = mission;
        Data.MegaMissionF.Target = target;
        Data.MegaMissionF.Destination = destination;
        Data.MegaMissionF.Speed = formation_speed;
        Data.MegaMissionF.MaxSpeed = max_speed;
        Frame = ::Frame;
        return;
    }
    House = 0xFF;
    Type = 0;
    Frame = ::Frame;
}

