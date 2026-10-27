// DynamicVectorClass<FootClass *>::ID_pointer (0x004CDEE0; DynamicVectorClass<FootClass *> vtable 0x007a1234 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class FootClass;

template class DynamicVectorClass<FootClass *>;
