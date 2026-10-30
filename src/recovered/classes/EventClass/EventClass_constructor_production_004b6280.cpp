// EventClass::EventClass(int house, int type, int rtti, int id, int naval) (0x004B6280)
// A production event: kind, id and naval at +0x07, +0x0B and +0x0F.
#include "shared/event.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?EventNames@@3PAPBDA=007d65cc
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BB@FOCK@Adding?5event?5?$CFs?6?$AA@=007d6890

EventClass::EventClass(int house, int type, int rtti, int id, int naval)
{
    Debug_Printf("Adding event %s\n", EventNames[(unsigned char)type]);
    if (house >= 0) {
        House = house;
        Type = type;
        Data.LongsCell.Long1 = rtti;
        Data.LongsCell.Long2 = id;
        Data.LongsCell.Long3 = naval;
    } else {
        House = 0xFF;
        Type = 0;
    }
    Frame = ::Frame;
}
