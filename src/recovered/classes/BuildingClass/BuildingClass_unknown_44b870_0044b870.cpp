// void BuildingClass::unknown_44b870(int arg1, CoordStruct const &coord) (0x0044B870)
// Records arg1, the type's DelayedFireDelay and the coordinate (unknown_5c8,
// unknown_5d8, unknown_5cc), ends animation 3 and starts animation 10 in the
// state the health gives.
#include "shared/building.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_44cfd0@BuildingClass@@QAEXH@Z=0044cfd0

void BuildingClass::unknown_44b870(int arg1, CoordStruct const &coord)
{
    unknown_5d8 = Type->DelayedFireDelay;
    unknown_5c8 = arg1;
    memcpy(&unknown_5cc, &coord, sizeof(unknown_5cc));
    unknown_44cfd0(3);
    unknown_44c920(10, Health_Ratio() <= Rules->unknown_1368, false, 0);
}
