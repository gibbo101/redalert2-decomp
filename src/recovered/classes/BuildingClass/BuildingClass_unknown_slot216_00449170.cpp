// void BuildingClass::unknown_slot216(int arg1) (0x00449170, slot 216)
// For a non-zero argument and a house that is the player's
// (HouseClass 0x004F52B0), remembers the building's cell in the radar
// event ring (0x0063C6C0).
#include "shared/building.hpp"
#include "shared/object.hpp"
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_0063C6C0@@YIXABVCell@@@Z=0063c6c0

void __fastcall Unknown_0063C6C0(Cell const &cell);       // 0x0063C6C0 (RadarEventClass: remembers a cell)

void BuildingClass::unknown_slot216(int arg1)
{
    if (arg1 && House->Unknown_004F52B0()) {
        Unknown_0063C6C0(Coord_Cell(unknown_slot19(0)));
    }
}
