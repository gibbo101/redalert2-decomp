// DynamicVectorClass<TagClass *>::ID_pointer (0x004D49D0; DynamicVectorClass<TagClass *> vtable 0x007a2ae4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class TagClass;

template class DynamicVectorClass<TagClass *>;
