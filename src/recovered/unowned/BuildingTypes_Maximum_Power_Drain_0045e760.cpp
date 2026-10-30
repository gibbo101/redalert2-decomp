// 0045E760: greatest base power drain in a building-type list; zero for an empty list.
// The original entry has no recorded incoming reference; the parameter's list identity
// follows its +4 vector pointer and +0x10 count. Exact nominal source signature unknown.
#include "shared/building_type.hpp"
#include "shared/type_list.hpp"
int __fastcall BuildingTypes_Maximum_Power_Drain_0045e760(DynamicVectorClass<BuildingTypeClass *> const &types)
{
    int maximum = 0;
    for (int index = 0; index < types.Count(); ++index) {
        int drain = types[index]->PowerDrain_c6c;
        if (drain > maximum) maximum = drain;
    }
    return maximum;
}
