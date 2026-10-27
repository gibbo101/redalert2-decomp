// SmudgeClass::SmudgeClass(SmudgeTypeClass *type, CoordStruct const &coord, int house) (0x006875C0)
// Registers the smudge and places it at the coordinate (unless it is the
// zero coordinate) for the given house; a smudge that cannot be placed is
// removed again (slot 60).
// Assumptions: slot 53 places an object (Unlimbo); the house global at
// 0x007F4230 is read while placing.
#include "shared/smudge.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?unknown_slot53@ObjectClass@@UAE_NABUCoordStruct@@H@Z=005d3890
// @ref ?unknown_slot60@ObjectClass@@UAEXXZ=005d4e90
// @ref ?unknown_placing_house_7f4230@@3HA=007f4230
// @ref ?Smudges@@3V?$DynamicVectorClass@PAVSmudgeClass@@@@A=00a3d240
// @ref _unknown_geometry_l=00abcee8
// @ref ??_7SmudgeClass@@6BIPersistStream@@@=007ab58c
// @ref ??_7SmudgeClass@@6BIRTTITypeInfo@@@=007ab568
// @ref ??_7SmudgeClass@@6BINoticeSink@@@=007ab584
// @ref ??_7SmudgeClass@@6BINoticeSource@@@=007ab560

SmudgeClass::SmudgeClass(SmudgeTypeClass *type, CoordStruct const &coord, int house) :
    Class(type)
{
    AbstractClass::Create_ID();
    Smudges.Add(this);
    if (coord.X != unknown_geometry_l.X || coord.Y != unknown_geometry_l.Y || coord.Z != unknown_geometry_l.Z) {
        unknown_placing_house_7f4230 = house;
        if (!ObjectClass::unknown_slot53(&coord, 0)) {
            ObjectClass::unknown_slot60();
            return;
        }
        unknown_placing_house_7f4230 = -1;
    }
}
