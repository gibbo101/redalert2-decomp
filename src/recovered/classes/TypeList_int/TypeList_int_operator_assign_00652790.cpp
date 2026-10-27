// TypeList<int>::operator=(TypeList<int> const &) -- 0x00652790
// The implicit assignment (DynamicVectorClass's assignment expanded, then
// the list's own +0x18 field), kept out of line in the Rules unit for
// the integer lists; element type from the callers: the source lists come from CCINIClass::Get_Integer_List (0x0046B1B0) and the temporary is destroyed through VectorClass<int> (vtable 0x0079D9D4, 0x00652810); 18 call sites 0x00646728-0x0064B1D4.
// Layout and behaviour: shared/type_list.hpp, shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
#include "shared/type_list.hpp"

template <>
TypeList<int> &TypeList<int>::operator=(TypeList<int> const &list)
{
    DynamicVectorClass<int>::operator=(list);
    unknown_0x18 = list.unknown_0x18;
    return *this;
}
