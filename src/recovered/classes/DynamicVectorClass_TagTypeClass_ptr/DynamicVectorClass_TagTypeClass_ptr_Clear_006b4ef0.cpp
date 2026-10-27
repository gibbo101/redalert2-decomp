// DynamicVectorClass<TagTypeClass *>::Clear (0x006B4EF0; DynamicVectorClass<TagTypeClass *> vtable 0x007ac778 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TagTypeClass;

template class DynamicVectorClass<TagTypeClass *>;
