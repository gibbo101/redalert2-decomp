// EventClass::EventClass(int house, unsigned char type, Cell const &cell) (0x004B5F60)
// The cell at +0x07 (TibSun's SellCell shape).
#include "shared/event.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?EventNames@@3PAPBDA=007d65cc
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BB@FOCK@Adding?5event?5?$CFs?6?$AA@=007d6890

EventClass::EventClass(int house, unsigned char type, Cell const &cell)
{
    Debug_Printf("Adding event %s\n", EventNames[type]);
    if (house >= 0) {
        House = house;
        Type = type;
        ShortAt(0x07) = cell.X;
        ShortAt(0x09) = cell.Y;
    } else {
        House = 0xFF;
        Type = 0;
    }
    Frame = ::Frame;
}
