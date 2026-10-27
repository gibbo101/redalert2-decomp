// OverlayClass::OverlayClass(OverlayTypeClass *type, Cell const &cell, int house) (0x005DA7D0)
// Registers the overlay and places it at the centre of the cell (unless it
// is the zero cell) for the given house.
// Assumptions: slot 53 places an object (Unlimbo); the house global at
// 0x007E8A8C is read while placing.
#include "shared/overlay.hpp"
// @ref _unknown_geometry_k=00a73088
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?unknown_slot53@ObjectClass@@UAE_NPBUCoordStruct@@H@Z=005d3890
// @ref ?unknown_placing_house_7e8a8c@@3HA=007e8a8c
// @ref ?unknown_OverlayClass_list_00a40c00@@3V?$DynamicVectorClass@PAVOverlayClass@@@@A=00a40c00
// @ref ??_7OverlayClass@@6BIPersistStream@@@=007a77f4
// @ref ??_7OverlayClass@@6BIRTTITypeInfo@@@=007a77d0
// @ref ??_7OverlayClass@@6BINoticeSink@@@=007a77ec
// @ref ??_7OverlayClass@@6BINoticeSource@@@=007a77c8

OverlayClass::OverlayClass(OverlayTypeClass *type, Cell const &cell, int house) :
    Class(type)
{
    AbstractClass::Create_ID();
    unknown_OverlayClass_list_00a40c00.Add(this);
    if (cell.X != unknown_geometry_k.X || cell.Y != unknown_geometry_k.Y) {
        unknown_placing_house_7e8a8c = house;
        CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
        ObjectClass::unknown_slot53(&coord, 0);
        unknown_placing_house_7e8a8c = -1;
    }
}
