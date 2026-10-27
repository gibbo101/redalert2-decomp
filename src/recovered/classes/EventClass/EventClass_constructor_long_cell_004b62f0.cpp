// EventClass::EventClass(int house, int type, long a, Cell const &cell) (0x004B62F0)
#include "shared/event.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?EventNames@@3PAPBDA=007d65cc
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BB@FOCK@Adding?5event?5?$CFs?6?$AA@=007d6890

EventClass::EventClass(int house, int type, long a, Cell const &cell)
{
    Debug_Printf("Adding event %s\n", EventNames[(unsigned char)type]);
    if (house >= 0) {
        House = house;
        Type = type;
        LongAt(0x07) = a;
        LongAt(0x0b) = -1;
        LongAt(0x0f) = 0;
        ShortAt(0x13) = cell.X;
        ShortAt(0x15) = cell.Y;
    } else {
        House = 0xFF;
        Type = 0;
    }
    Frame = ::Frame;
}
