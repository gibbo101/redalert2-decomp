#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/unknown_loadout.hpp"
#include "shared/techno_type.hpp"
#include "shared/type_list.hpp"
#include "shared/id_source.hpp"
int __fastcall Unknown4A6AE0Owner::Find_Type_Index_004A6B50(TechnoTypeClass *type)
{
    int count = unknown_id_source_a3d290->AllowableUnits.Count();
    if (!count) return -1;
    for (int index = 0; index < count; ++index) {
        if (unknown_id_source_a3d290->AllowableUnits[index] == type
            && unknown_id_source_a3d290->AllowableUnitMaximums[index] != -1) return index;
    }
    return -1;
}
