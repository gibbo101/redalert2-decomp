// VectorClass<ScriptClass *>::ID_object (0x0040E790; VectorClass<ScriptClass *> vtable 0x0079ab34 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class ScriptClass;

template class VectorClass<ScriptClass *>;
