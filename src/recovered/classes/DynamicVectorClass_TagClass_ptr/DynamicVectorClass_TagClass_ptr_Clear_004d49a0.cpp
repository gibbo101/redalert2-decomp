// DynamicVectorClass<TagClass *>::Clear (0x004D49A0; DynamicVectorClass<TagClass *> vtable 0x007a2ae4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TagClass;

template class DynamicVectorClass<TagClass *>;
