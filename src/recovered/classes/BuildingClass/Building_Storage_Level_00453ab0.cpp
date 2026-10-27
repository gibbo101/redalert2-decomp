// Scale stored amount by four and divide by capacity, preserving both ordered reads.
// Free fastcall versus original Building member source spelling is unproved.
#include "shared/building.hpp"
// @ref ?unknown_69ae10@UnknownQuad@@QBEMXZ=0069ae10
int __fastcall Building_Storage_Level_00453ab0(BuildingClass *building)
{
    if ((int)building->unknown_294.unknown_69ae10() == 0)
        return 0;
    return (int)((unsigned int)(int)building->unknown_294.unknown_69ae10() * 4u)
           / building->Type->Storage;
}
