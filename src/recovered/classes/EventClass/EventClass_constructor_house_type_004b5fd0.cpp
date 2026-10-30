// EventClass::EventClass(int house, unsigned char type) (0x004B5FD0)
// An event with only a house and a type (Red Alert's EventClass(EventType)).
#include "shared/event.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?EventNames@@3PAPBDA=007d65cc
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BB@FOCK@Adding?5event?5?$CFs?6?$AA@=007d6890

EventClass::EventClass(int house, unsigned char type)
{
    Debug_Printf("Adding event %s\n", EventNames[type]);
    if (house >= 0) {
        House = house;
        Type = type;
    } else {
        House = 0xFF;
        Type = 0;
    }
    Frame = ::Frame;
}
