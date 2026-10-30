// EventClass::EventClass(int house, unsigned char type, int rtti, int id) (0x004B64F0)
// Two longs at +0x07 and +0x0B (TibSun's object-and-id shape).
#include "shared/event.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?EventNames@@3PAPBDA=007d65cc
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BB@FOCK@Adding?5event?5?$CFs?6?$AA@=007d6890

EventClass::EventClass(int house, unsigned char type, int rtti, int id)
{
    Debug_Printf("Adding event %s\n", EventNames[type]);
    if (house >= 0) {
        House = house;
        Type = type;
        LongAt(0x07) = rtti;
        LongAt(0x0B) = id;
    } else {
        House = 0xFF;
        Type = 0;
    }
    Frame = ::Frame;
}
