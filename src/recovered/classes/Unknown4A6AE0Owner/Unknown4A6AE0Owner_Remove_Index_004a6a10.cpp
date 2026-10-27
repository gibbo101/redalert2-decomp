#include "shared/unknown_loadout.hpp"
#include "shared/techno_type.hpp"
#include "shared/type_list.hpp"
#include "shared/id_source.hpp"
bool Unknown4A6AE0Owner::Remove_Index_004A6A10(int index)
{
    if (Count <= 0 || index < 0 || index >= Count) return false;
    int scenarioIndex = Find_Type_Index_004A6B50(Types[index]);
    if (scenarioIndex != -1) --unknown_id_source_a3d290->Loadout_Counts_228c()[scenarioIndex];
    Cost -= Types[index]->Raw_Cost();
    for (int slot = index; slot < Count - 1; ++slot) {
        Types[slot] = Types[slot + 1];
    }
    Types[--Count] = 0;
    return true;
}

