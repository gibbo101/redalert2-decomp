// DynamicVectorClass<TiberiumClass *>::ID_pointer (0x006EAA40; DynamicVectorClass<TiberiumClass *> vtable 0x007ad844 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class TiberiumClass;

template class DynamicVectorClass<TiberiumClass *>;
