#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/unknown_loadout.hpp"
#include "shared/techno_type.hpp"
#include "shared/type_list.hpp"
#include "shared/id_source.hpp"
bool Unknown4A6AE0Owner::Add_Type_004A6940(TechnoTypeClass *type)
{
    if (Count < 5) {
        int index = Find_Type_Index_004A6B50(type);
        if (index == -1 || unknown_id_source_a3d290->Loadout_Counts_228c()[index]
            < unknown_id_source_a3d290->Loadout_Limits_2270()[index]) {
            Types[Count++] = type;
            Cost += type->Raw_Cost();
            if (index != -1) ++unknown_id_source_a3d290->Loadout_Counts_228c()[index];
            return true;
        }
    }
    return false;
}

