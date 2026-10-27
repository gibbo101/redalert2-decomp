// DynamicVectorClass<ScriptTypeClass *>::Clear (0x004D5310; DynamicVectorClass<ScriptTypeClass *> vtable 0x007a2664 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class ScriptTypeClass;

template class DynamicVectorClass<ScriptTypeClass *>;
