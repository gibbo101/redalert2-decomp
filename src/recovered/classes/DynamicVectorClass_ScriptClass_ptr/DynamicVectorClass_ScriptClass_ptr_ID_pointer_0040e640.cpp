// DynamicVectorClass<ScriptClass *>::ID_pointer (0x0040E640; DynamicVectorClass<ScriptClass *> vtable 0x0079ab14 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class ScriptClass;

template class DynamicVectorClass<ScriptClass *>;
