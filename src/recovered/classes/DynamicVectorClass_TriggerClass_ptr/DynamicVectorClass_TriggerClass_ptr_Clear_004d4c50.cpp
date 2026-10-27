// DynamicVectorClass<TriggerClass *>::Clear (0x004D4C50; DynamicVectorClass<TriggerClass *> vtable 0x007a2124 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TriggerClass;

template class DynamicVectorClass<TriggerClass *>;
