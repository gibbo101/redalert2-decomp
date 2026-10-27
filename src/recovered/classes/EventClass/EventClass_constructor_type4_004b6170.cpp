// EventClass::EventClass(int house, TargetClass whom, unsigned char mission, TargetClass target, TargetClass destination, TargetClass follow) (0x004B6170): event type 4.
#include "shared/event.hpp"
// @ref ?Frame@@3HA=00a40d2c

EventClass::EventClass(int house, TargetClass whom, unsigned char mission, TargetClass target, TargetClass destination, TargetClass follow)
{
    if (house >= 0) {
        House = house;
        Type = 4;
        ByteAt(0x1d) = 0;
        TargetAt(0x07) = whom;
        ByteAt(0x0c) = mission;
        TargetAt(0x0e) = target;
        TargetAt(0x13) = destination;
        TargetAt(0x18) = follow;
        Frame = ::Frame;
        return;
    }
    House = 0xFF;
    Type = 0;
    Frame = ::Frame;
}
