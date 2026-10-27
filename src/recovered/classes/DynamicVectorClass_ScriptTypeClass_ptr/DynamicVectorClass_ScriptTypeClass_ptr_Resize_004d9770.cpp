// DynamicVectorClass<ScriptTypeClass *>::Resize (0x004D9770; DynamicVectorClass<ScriptTypeClass *> vtable 0x007a2664 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class ScriptTypeClass;

template class DynamicVectorClass<ScriptTypeClass *>;
