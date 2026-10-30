// Money urgency, original004E8D80;827body bytes. RA2 checks two alternatives.
#include "shared/unit.hpp"
#include "shared/building_type_class.hpp"
#include "shared/factory_class.hpp"
#include "shared/rules.hpp"
// @ref ?Can_Make_Money_004e27e0@HouseClass@@QAE_NXZ=004e27e0
// @ref ?Get_Object@FactoryClass@@QBEPAVTechnoClass@@XZ=004b9930

int HouseClass::Check_Raise_Money_004e8d80()
{
    int urgency=0;
    if (Is_Human_Control()) return 0;
    if (!Can_Make_Money_004e27e0()) {
        bool has_refinery=unknown_5460.unknown_func_491d10(Rules->BuildRefinery[0]->ArrayIndex)>0 ||
                          unknown_5460.unknown_func_491d10(Rules->BuildRefinery[1]->ArrayIndex)>0;
        if (has_refinery) {
            for (int index=0;index<unknown_BuildingClass_list_00a40af8.Count();++index) {
                BuildingClass *building=unknown_BuildingClass_list_00a40af8[index];
                if (building->House==this &&
                    (building->Type==Rules->BuildRefinery[0] || building->Type==Rules->BuildRefinery[1]) &&
                    building->Mission==18) return 0;
            }
            if (unknown_5540!=Rules->unknown_9ec[0]->ArrayIndex &&
                unknown_5540!=Rules->unknown_9ec[1]->ArrayIndex) {
                if (Available_Money()<Rules->unknown_9ec[0]->unknown_slot33((int)this) &&
                    Available_Money()<Rules->unknown_9ec[1]->unknown_slot33((int)this)) urgency=1;
            } else {
            FactoryClass *pending=0;
            for (int factory_index=0;factory_index<Factories.Count();++factory_index) {
                if (Factories[factory_index]->Get_House_004e4090()==this && Factories[factory_index]->Get_Object()!=0) {
                    UnitClass *unit=(UnitClass *)Factories[factory_index]->Get_Object();
                    if (unit->Kind_Of()==1 &&
                        (unit->Type==Rules->unknown_9ec[0] || unit->Type==Rules->unknown_9ec[1])) {
                        pending=Factories[factory_index];
                        break;
                    }
                }
            }
            if (pending) {
                int owed=pending->UnspentCost;
                if (Available_Money()<owed) urgency=1;
            } else urgency=1;
            }
        } else {
            if (unknown_553c!=Rules->BuildRefinery[0]->ArrayIndex &&
                unknown_553c!=Rules->BuildRefinery[1]->ArrayIndex) {
                if (Available_Money()<Rules->BuildRefinery[0]->unknown_slot33((int)this) &&
                    Available_Money()<Rules->BuildRefinery[1]->unknown_slot33((int)this)) urgency=1;
            } else {
            FactoryClass *pending=0;
            for (int factory_index=0;factory_index<Factories.Count();++factory_index) {
                if (Factories[factory_index]->Get_House_004e4090()==this && Factories[factory_index]->Get_Object()!=0) {
                    BuildingClass *building=(BuildingClass *)Factories[factory_index]->Get_Object();
                    if (building->Kind_Of()==6 &&
                        (building->Type==Rules->BuildRefinery[0] || building->Type==Rules->BuildRefinery[1])) {
                        pending=Factories[factory_index];
                        break;
                    }
                }
            }
            if (pending) {
                int owed=pending->UnspentCost;
                if (Available_Money()<owed) urgency=1;
            } else urgency=1;
            }
        }
    }
    return urgency;
}
