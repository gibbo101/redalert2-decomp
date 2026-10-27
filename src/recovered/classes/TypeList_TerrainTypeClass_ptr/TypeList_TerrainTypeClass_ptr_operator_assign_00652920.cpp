// TypeList<TerrainTypeClass *>::operator=(TypeList<TerrainTypeClass *> const &) -- 0x00652920
// The implicit assignment (DynamicVectorClass's assignment expanded, then
// the list's own +0x18 field), kept out of line in the Rules unit for
// the terrain type lists; element type from the callers: the temporary read by 0x00654150 ("DefaultMirageDisguises", 0x0064B550) is destroyed through VectorClass<TerrainTypeClass *> (vtable 0x007A9158, 0x00652870).
// Layout and behaviour: shared/type_list.hpp, shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
#include "shared/type_list.hpp"

class TerrainTypeClass;

template <>
TypeList<TerrainTypeClass *> &TypeList<TerrainTypeClass *>::operator=(TypeList<TerrainTypeClass *> const &list)
{
    DynamicVectorClass<TerrainTypeClass *>::operator=(list);
    unknown_0x18 = list.unknown_0x18;
    return *this;
}
