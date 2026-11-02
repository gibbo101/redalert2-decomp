// @ref ??_7?$VectorClass@PAVBuildingTypeClass@@@@6B@=007a2784
// @ref ??_G?$VectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004dce60
// @ref ??_E?$VectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004dce60
// @ref ??8?$VectorClass@PAVBuildingTypeClass@@@@UBE_NABV0@@Z=004d9f70
// @ref ?Resize@?$VectorClass@PAVBuildingTypeClass@@@@UAE_NHPBQAVBuildingTypeClass@@@Z=004d9fb0
// @ref ?Clear@?$VectorClass@PAVBuildingTypeClass@@@@UAEXXZ=004da060
// @ref ?ID@?$VectorClass@PAVBuildingTypeClass@@@@UAEHABQAVBuildingTypeClass@@@Z=004da090
// @ref ?ID@?$VectorClass@PAVBuildingTypeClass@@@@UAEHPBQAVBuildingTypeClass@@@Z=004da0d0
// @ref ?Fetch@?$VectorClass@PAVBuildingTypeClass@@@@UBEPAVBuildingTypeClass@@H@Z=004d54e0
// @ref ??_G?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004dceb0
// @ref ??_E?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004dceb0
// @ref ?Resize@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAE_NHPBQAVBuildingTypeClass@@@Z=004da0f0
// @ref ?Clear@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEXXZ=004d5490
// @ref ?ID@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEHABQAVBuildingTypeClass@@@Z=004da1a0
// @ref ?ID@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEHPBQAVBuildingTypeClass@@@Z=004d54c0
// House defense candidates, original 004f1ff0; independently bounded 405+11.
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ??0?$VectorClass@PAVBuildingTypeClass@@@@QAE@IPBQAVBuildingTypeClass@@@Z=004f8900
// @ref ??_7?$VectorClass@PAVBuildingTypeClass@@@@6B@=007a2784
// @ref ??_7?$DynamicVectorClass@PAVBuildingTypeClass@@@@6B@=007a2764
#include "shared/house.hpp"
#include "shared/building_type_class.hpp"
#include "shared/building_type_list.hpp"
DynamicVectorClass<BuildingTypeClass *> HouseClass::Get_Anti_Armor_Defense_Buildings_004f1ff0(DynamicVectorClass<BuildingTypeClass const *> &owned)
{
    unsigned ownable = 1 << HouseTypeClass::Find_Index(Type->ParentCountry);
    DynamicVectorClass<BuildingTypeClass *> defenses;
    for (int i = 0; i < BuildingTypes.Count(); ++i) {
        BuildingTypeClass *building = BuildingTypes[i];
        if ((building->Owner & ownable) && building->unknown_11dc > 0 && building->TechLevel <= unknown_11c && unknown_func_4ef740(building, owned, owned.Count())) {
            defenses.Add(building);
        }
    }
    return defenses;
}
