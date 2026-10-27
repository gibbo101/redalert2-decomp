// DynamicVectorClass<ScriptClass *>::Clear (0x0040E610; DynamicVectorClass<ScriptClass *> vtable 0x0079ab14 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class ScriptClass;

template class DynamicVectorClass<ScriptClass *>;
