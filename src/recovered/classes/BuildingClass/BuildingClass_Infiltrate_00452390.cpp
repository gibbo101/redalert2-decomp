// Agent infiltration: disrupt radar/power/super, steal credits or grant technology.
#include "shared/building.hpp"
#include "shared/foot.hpp"
#include "shared/rules.hpp"
extern bool unknown_flag_8373c2;
// @ref ?unknown_flag_8373c2@@3_NA=008373c2
// EVA_NewTechnologyAcquired
extern char const unknown_eva_007cfaac[];
// @ref ?unknown_eva_007cfaac@@3QBDB=007cfaac
// EVA_TechnologyStolen
extern char const unknown_eva_007cfac8[];
// @ref ?unknown_eva_007cfac8@@3QBDB=007cfac8
// EVA_BuildingInfCashStolen
extern char const unknown_eva_007cfae0[];
// @ref ?unknown_eva_007cfae0@@3QBDB=007cfae0
// EVA_CashStolen
extern char const unknown_eva_007cfafc[];
// @ref ?unknown_eva_007cfafc@@3QBDB=007cfafc
// EVA_EnemyBasePoweredDown
extern char const unknown_eva_007cfb0c[];
// @ref ?unknown_eva_007cfb0c@@3QBDB=007cfb0c
// EVA_BuildingInfiltrated
extern char const unknown_eva_007cfb28[];
// @ref ?unknown_eva_007cfb28@@3QBDB=007cfb28
// EVA_PowerSabotaged
extern char const unknown_eva_007cfb40[];
// @ref ?unknown_eva_007cfb40@@3QBDB=007cfb40
// EVA_BuildingInfRadarSabotaged
extern char const unknown_eva_007cfb54[];
// @ref ?unknown_eva_007cfb54@@3QBDB=007cfb54
// EVA_RadarSabotaged
extern char const unknown_eva_007cfb74[];
// @ref ?unknown_eva_007cfb74@@3QBDB=007cfb74

// @ref ?unknown_69ebb0@SuperClass@@QAEXXZ=0069ebb0
void BuildingClass::Unknown_00452390(HouseClass *house)
{
    bool visible = false;
    if(House->Unknown_004F52B0() || house->Unknown_004F52B0()) {
        if(Unknown_0063B5B0(9, unknown_slot104())) visible = true;
    }
    BuildingTypeClass *type = Type;
    if(type->Radar) {
        House->unknown_func_4f5880();
        if(House->Unknown_004F52B0() && !House->unknown_566a && visible)
            Unknown_00715B40(unknown_eva_007cfb74,-1,-1);
        if(house->Unknown_004F52B0() && !House->unknown_566a && visible)
            Unknown_00715B40(unknown_eva_007cfb54,-1,-1);
    } else if(type->Power > 0) {
        House->unknown_func_4f5800(Rules->SpyPowerBlackout);
        if(House->Unknown_004F52B0() && visible) {
            Unknown_00715B40(unknown_eva_007cfb40,-1,-1);
        } else if(house->Unknown_004F52B0() && visible) {
            Unknown_00715B40(unknown_eva_007cfb28,-1,-1);
            Unknown_00715B40(unknown_eva_007cfb0c,-1,-1);
        }
    } else if(type->SuperWeapon != -1) {
        House->Supers[type->SuperWeapon]->unknown_69ebb0();
        if(House->Unknown_004F52B0() || (house->Unknown_004F52B0() && visible))
            Unknown_00715B40(unknown_eva_007cfb28,-1,-1);
    } else {
        for(int index=0;index<Rules->BuildTech.Count();++index) {
            if(Rules->BuildTech[index] == type) {
                if(House->unknown_130 == 0) house->unknown_205 = true;
                else house->unknown_204 = true;
                house->unknown_144 = true;
                if(House->Unknown_004F52B0() && visible)
                    Unknown_00715B40(unknown_eva_007cfac8,-1,-1);
                if(house->Unknown_004F52B0() && visible) {
                    Unknown_00715B40(unknown_eva_007cfb28,-1,-1);
                    Unknown_00715B40(unknown_eva_007cfaac,-1,-1);
                }
                goto finished;
            }
        }
        if(type->Storage > 0) {
            int stolen = (int)(House->Available_Money() * Rules->SpyMoneyStealPercent);
            House->Unknown_004E5280(stolen);
            house->Refund_Money(stolen);
            if(House->Unknown_004F52B0() && visible)
                Unknown_00715B40(unknown_eva_007cfafc,-1,-1);
            if(house->Unknown_004F52B0() && visible)
                Unknown_00715B40(unknown_eva_007cfae0,-1,-1);
        } else if(type->Factory == 40) {
            house->unknown_207 = true;
            house->unknown_144 = true;
            if(house->Unknown_004F52B0()) unknown_flag_8373c2 = true;
            if(House->Unknown_004F52B0() && visible)
                Unknown_00715B40(unknown_eva_007cfac8,-1,-1);
            if(house->Unknown_004F52B0() && visible) {
                Unknown_00715B40(unknown_eva_007cfb28,-1,-1);
                Unknown_00715B40(unknown_eva_007cfaac,-1,-1);
            }

        } else if(type->Factory == 16) {
            house->unknown_206 = true;
            house->unknown_144 = true;
            if(house->Unknown_004F52B0()) unknown_flag_8373c2 = true;
            if(House->Unknown_004F52B0() && visible)
                Unknown_00715B40(unknown_eva_007cfac8,-1,-1);
            if(house->Unknown_004F52B0() && visible) {
                Unknown_00715B40(unknown_eva_007cfb28,-1,-1);
                Unknown_00715B40(unknown_eva_007cfaac,-1,-1);
            }
        }
    }
finished:
    unknown_slot71(2);
}
