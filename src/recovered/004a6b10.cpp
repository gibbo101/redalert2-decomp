#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/unknown_loadout.hpp"
#include "shared/techno_type.hpp"
#include "shared/id_source.hpp"
void Unknown4A6AE0Owner::Swizzle_Types_004A6B10()
{
    for (int index = 0; index < Count; ++index) {
        SwizzleManager.Swizzle((void **)&Types[index]);
    }
}

