// DynamicVectorClass<ScriptClass *>::Resize (0x0040E7F0; DynamicVectorClass<ScriptClass *> vtable 0x0079ab14 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class ScriptClass;

template class DynamicVectorClass<ScriptClass *>;
