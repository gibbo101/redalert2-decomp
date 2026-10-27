// DynamicVectorClass<ScriptTypeClass *>::ID_object (0x004D9820; DynamicVectorClass<ScriptTypeClass *> vtable 0x007a2664 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class ScriptTypeClass;

template class DynamicVectorClass<ScriptTypeClass *>;
