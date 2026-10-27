// TypeList<BuildingTypeClass *>::operator=(TypeList<BuildingTypeClass *> const &) -- 0x006529A0
// The implicit assignment (DynamicVectorClass's assignment expanded, then
// the list's own +0x18 field), kept out of line in the Rules unit for
// the building type lists; element type from the callers: the temporary read by 0x00653BD0 (e.g. "BuildNavalYard", 0x0064CE99) is destroyed through VectorClass<BuildingTypeClass *> (vtable 0x007A2F08).
// Layout and behaviour: shared/type_list.hpp, shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
#include "shared/type_list.hpp"

class BuildingTypeClass;

template <>
TypeList<BuildingTypeClass *> &TypeList<BuildingTypeClass *>::operator=(TypeList<BuildingTypeClass *> const &list)
{
    DynamicVectorClass<BuildingTypeClass *>::operator=(list);
    unknown_0x18 = list.unknown_0x18;
    return *this;
}
