// TypeList<InfantryTypeClass *>::operator=(TypeList<InfantryTypeClass *> const &) -- 0x006528A0
// The implicit assignment (DynamicVectorClass's assignment expanded, then
// the list's own +0x18 field), kept out of line in the Rules unit for
// the infantry type lists; element type from the callers: the temporary read by 0x00653E90 (e.g. "AllyParaDropInf", 0x0064A150) is destroyed through VectorClass<InfantryTypeClass *> (vtable 0x007A3118, 0x00652840).
// Layout and behaviour: shared/type_list.hpp, shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
#include "shared/type_list.hpp"

class InfantryTypeClass;

template <>
TypeList<InfantryTypeClass *> &TypeList<InfantryTypeClass *>::operator=(TypeList<InfantryTypeClass *> const &list)
{
    DynamicVectorClass<InfantryTypeClass *>::operator=(list);
    unknown_0x18 = list.unknown_0x18;
    return *this;
}
