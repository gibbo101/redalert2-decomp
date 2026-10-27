// DynamicVectorClass<ScriptTypeClass *>::ID_pointer (0x004D5340; DynamicVectorClass<ScriptTypeClass *> vtable 0x007a2664 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class ScriptTypeClass;

template class DynamicVectorClass<ScriptTypeClass *>;
