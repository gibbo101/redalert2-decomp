// void HouseClass::unknown_func_4eea40() (0x004EEA40)
// Turns the house's firestorm off (+0x142): every FirestormWall building it
// owns switches (0x00450950) and the map rebuilds the zones of their cells.
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??0?$VectorClass@VCell@@@@QAE@HPBVCell@@@Z=0042d4a0
// @ref ?Update_Firestorm_Wall_00450950@BuildingClass@@QAEXXZ=00450950
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_E?$DynamicVectorClass@VCell@@@@UAEPAXI@Z=0042d3e0
// @ref ??8?$VectorClass@VCell@@@@UBE_NABV0@@Z=0042ce10
// @ref ?Resize@?$DynamicVectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042d050
// @ref ?Clear@?$DynamicVectorClass@VCell@@@@UAEXXZ=0042cc10
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHABVCell@@@Z=0042d120
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHPBVCell@@@Z=0042cc40
// @ref ?Fetch@?$VectorClass@VCell@@@@UBE?AVCell@@H@Z=0042cc60
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??_E?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ?Resize@?$VectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042cee0
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHABVCell@@@Z=0042cfe0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHPBVCell@@@Z=0042d030

void HouseClass::unknown_func_4eea40()
{
    if (unknown_142) {
        unknown_142 = false;
        DynamicVectorClass<Cell> cells;
        for (int index = unknown_BuildingClass_list_00a40af8.Count() - 1; index >= 0; index--) {
            BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
            if (building->Type->FirestormWall && building->House == this) {
                building->Update_Firestorm_Wall_00450950();
                cells.Add(Coord_Cell(building->Center_Coord()));
            }
        }
        Map.Unknown_0054EBD0();
        Map.Unknown_005688A0(cells);
    }
}
