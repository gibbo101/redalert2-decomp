// DynamicVectorClass<TiberiumClass *>::Clear (0x006EAA10; DynamicVectorClass<TiberiumClass *> vtable 0x007ad844 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TiberiumClass;

template class DynamicVectorClass<TiberiumClass *>;
