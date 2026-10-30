// House income capability, original004E27E0;481body+15padding.
#include "shared/unit.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"

bool HouseClass::Can_Make_Money_004e27e0()
{
    int credits=Available_Money();
    int refinery_cost=unknown_func_4ef600(Rules->BuildRefinery)->unknown_slot33((int)this);
    int harvester_cost=Unknown_004EF6F0(Rules->unknown_9ec)->unknown_slot33((int)this);
    bool has_refinery=unknown_5460.unknown_func_491d10(Rules->BuildRefinery[0]->ArrayIndex)>0 ||
                      unknown_5460.unknown_func_491d10(Rules->BuildRefinery[1]->ArrayIndex)>0;
    bool has_harvester=unknown_5470.unknown_func_491d10(Rules->unknown_9ec[0]->ArrayIndex)>0 ||
                       unknown_5470.unknown_func_491d10(Rules->unknown_9ec[1]->ArrayIndex)>0;
    if (has_refinery) {
        if (has_harvester) return true;
        bool has_factory=false;
        for (int index=0;index<Rules->BuildWeapons.Count();++index) {
            has_factory=has_factory || unknown_5460.unknown_func_491d10(Rules->BuildWeapons[index]->ArrayIndex)>0;
        }
        int factory_cost=Rules->BuildWeapons[0]->unknown_slot33((int)this);
        if ((has_factory && credits>=harvester_cost) || credits>=harvester_cost+factory_cost ||
            credits>=refinery_cost) return true;
        return false;
    }
    if (credits>refinery_cost) return true;
    return false;
}
