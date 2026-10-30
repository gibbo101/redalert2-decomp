// EventClass::EventClass(int house, int type, unsigned long a) (0x004B6030)
// A four-byte payload at +0x07 (TibSun's EventClass(index, type, int val)).
#include "shared/event.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?EventNames@@3PAPBDA=007d65cc
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BB@FOCK@Adding?5event?5?$CFs?6?$AA@=007d6890

EventClass::EventClass(int house, int type, unsigned long a)
{
    Debug_Printf("Adding event %s\n", EventNames[(unsigned char)type]);
    if (house >= 0) {
        House = house;
        Type = type;
        LongAt(0x07) = a;
    } else {
        House = 0xFF;
        Type = 0;
    }
    Frame = ::Frame;
}
