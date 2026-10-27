// DynamicVectorClass<ScriptClass *>::ID_object (0x0040E8A0; DynamicVectorClass<ScriptClass *> vtable 0x0079ab14 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class ScriptClass;

template class DynamicVectorClass<ScriptClass *>;
