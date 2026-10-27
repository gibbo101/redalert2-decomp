// DynamicVectorClass<SmudgeClass *>::ID_pointer (0x004D4EC0; DynamicVectorClass<SmudgeClass *> vtable 0x007a22e4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class SmudgeClass;

template class DynamicVectorClass<SmudgeClass *>;
