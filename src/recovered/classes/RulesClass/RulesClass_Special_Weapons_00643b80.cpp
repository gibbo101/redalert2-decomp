// RulesClass::Special_Weapons (0x00643B80)
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_08BCFG@NukeDown?$AA@=007eef40
// @ref ??_C@_0BC@NJBC@EMPulseProjectile?$AA@=007eef1c
// @ref ??_C@_0L@PGEL@HSBuilding?$AA@=007eef68
// @ref ??_C@_0M@JLDN@NukeWarhead?$AA@=007eef5c
// @ref ??_C@_0P@DPMD@NukeProjectile?$AA@=007eef4c
// @ref ??_C@_0P@GHGL@EMPulseWarhead?$AA@=007eef30
// @ref ?Clear@?$VectorClass@PAVBuildingTypeClass@@@@UAEXXZ=004f7100
// @ref _RulesSection_SpecialWeapons=007a9038
// @ref ??_C@_0P@KHKN@SpecialWeapons?$AA@=007eecfc
// @ref ??_7?$DynamicVectorClass@PAVBuildingTypeClass@@@@6B@=007a2f28
// @ref ??_E?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004f84e0
// @ref ??_G?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004f84e0
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/warhead_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/building_type.hpp"

bool RulesClass::Special_Weapons(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_SpecialWeapons)) {
        HSBuilding = TypeListReader<BuildingTypeClass>::Get(ini, RulesSection_SpecialWeapons, "HSBuilding", HSBuilding);
        unknown_c60 = Get_Type(ini, RulesSection_SpecialWeapons, "NukeWarhead", unknown_c60);
        NukeProjectile = Get_Type(ini, RulesSection_SpecialWeapons, "NukeProjectile", NukeProjectile);
        NukeDown = Get_Type(ini, RulesSection_SpecialWeapons, "NukeDown", NukeDown);
        EMPulseWarhead = Get_Type(ini, RulesSection_SpecialWeapons, "EMPulseWarhead", EMPulseWarhead);
        EMPulseProjectile = Get_Type(ini, RulesSection_SpecialWeapons, "EMPulseProjectile", EMPulseProjectile);
        
        for (int index = 0; index < unknown_WarheadTypeClass_list_00839b00.Count(); index++) {
            unknown_WarheadTypeClass_list_00839b00[index]->Read_INI(ini);
        }
        return true;
    }
    return false;
}
