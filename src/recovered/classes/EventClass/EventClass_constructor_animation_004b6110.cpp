// EventClass::EventClass(int house, int anim, int owner, CoordStruct const &coord) (0x004B6110)
// ANIMATION (type 0x14): the anim type and owner at +0x07/+0x0B, the coordinate's X and Y at
// +0x0F/+0x13 (Execute takes Z from the map). TibSun's EventClass(index, AnimType, HousesType, Coord).
#include "shared/event.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BI@CGAG@Adding?5event?5ANIMATION?6?$AA@=007d68a4

EventClass::EventClass(int house, int anim, int owner, CoordStruct const &coord)
{
    Debug_Printf("Adding event ANIMATION\n");
    if (house >= 0) {
        House = house;
        Type = 0x14;
        Data.LongsCell.Long1 = anim;
        Data.LongsCell.Long2 = owner;
        Data.LongsCell.Long3 = coord.X;
        LongAt(0x13) = coord.Y;
    } else {
        House = 0xFF;
        Type = 0;
    }
    Frame = ::Frame;
}
