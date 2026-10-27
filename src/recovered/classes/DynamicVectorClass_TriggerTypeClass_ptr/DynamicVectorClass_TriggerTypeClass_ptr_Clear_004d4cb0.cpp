// DynamicVectorClass<TriggerTypeClass *>::Clear (0x004D4CB0; DynamicVectorClass<TriggerTypeClass *> vtable 0x007a20e4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TriggerTypeClass;

template class DynamicVectorClass<TriggerTypeClass *>;
