// static void BuildingTypeClass::unknown_func_45ebd0() (0x0045EBD0)
// Gives each type the isometric tile type its "ToTile" key (in the INI
// pointed to by 0x008396D0) names (unknown_bf0).
#include "shared/building_type.hpp"
#include "shared/ccini_class.hpp"
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ?unknown_ini_8396d0@@3PAVCCINIClass@@A=008396d0
// @ref ??_C@_06POHH@ToTile?$AA@=007d119c
// @ref ?Unknown_00529400@@YIHPBD@Z=00529400
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0

class IsometricTileTypeClass;
extern CCINIClass *unknown_ini_8396d0;                       // 0x008396D0
extern DynamicVectorClass<IsometricTileTypeClass *> IsoTileTypes;
int __fastcall Unknown_00529400(char const *name);           // 0x00529400 (IsometricTileTypeClass: the index by ID)

void BuildingTypeClass::unknown_func_45ebd0()
{
    for (int index = 0; index < BuildingTypes.Count(); index++) {
        BuildingTypeClass *type = BuildingTypes[index];
        char name[60];
        name[0] = 0;
        unknown_ini_8396d0->Get_String(type->ID, "ToTile", 0, name, 60);
        int tile = Unknown_00529400(name);
        if (tile >= 0 && tile < IsoTileTypes.Count()) {
            type->unknown_bf0 = IsoTileTypes[tile];
        }
    }
}
