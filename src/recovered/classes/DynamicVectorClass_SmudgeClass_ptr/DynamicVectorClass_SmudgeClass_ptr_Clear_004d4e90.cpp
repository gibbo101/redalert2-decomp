// DynamicVectorClass<SmudgeClass *>::Clear (0x004D4E90; DynamicVectorClass<SmudgeClass *> vtable 0x007a22e4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class SmudgeClass;

template class DynamicVectorClass<SmudgeClass *>;
