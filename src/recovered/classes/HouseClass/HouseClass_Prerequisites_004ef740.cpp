// 0x004EF740: checks each prerequisite against available building types.
// Original code 004EF740..004EF869; alignment through004EF86C;
// six switch targets end at004EF884. Full strict audit still required.
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"
#include "shared/building_type_list.hpp"
#include "shared/vector_class.hpp"

bool HouseClass::unknown_func_4ef740(BuildingTypeClass *type,
    DynamicVectorClass<BuildingTypeClass const *> &available, int count)
{
    int prerequisite = 0;
    if (type->Prerequisite.Count() > 0) {
        do {
            int index = type->Prerequisite[prerequisite];
            if (index >= 0) {
                int item = 0;
                if (count <= 0) return false;
                while (true) {
                    if (available[item] == BuildingTypes[index]) break;
                    ++item;
                    if (item >= count) return false;
                }
            } else {
                TypeList<BuildingTypeClass *> *group = 0;
                switch (index) {
                case -1: group = &Rules->BuildPower; break;
                case -2: group = &Rules->BuildWeapons; break;
                case -3: group = &Rules->BuildBarracks; break;
                case -4: group = &Rules->BuildRadar; break;
                case -5: group = &Rules->BuildTech; break;
                case -6: group = &Rules->BuildRefinery; break;
                }
                int member = 0;
                if (group->Count() > 0) {
                    do {
                        BuildingTypeClass *candidate = group->Fetch(member);
                        int item = 0;
                        if (count > 0) {
                            do {
                                if (available[item] == candidate) goto found;
                                ++item;
                            } while (item < count);
                        }
                        ++member;
                    } while (member < group->Count());
                }
                return false;
            }
found:
            ++prerequisite;
        } while (prerequisite < type->Prerequisite.Count());
    }
    return true;
}
