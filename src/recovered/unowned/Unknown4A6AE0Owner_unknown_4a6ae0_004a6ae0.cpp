#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/unknown_loadout.hpp"
#include "shared/techno_type.hpp"
#include "shared/id_source.hpp"
void Unknown4A6AE0Owner::Clear_004A6AE0()
{
    unknown_0c = false;
    for (int count = Count; count > 0; --count) Remove_Index_004A6A10(0);
    Count = 0;
    Cost = 0;
}

