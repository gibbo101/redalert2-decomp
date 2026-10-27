// VectorClass<ScriptClass *>::Fetch (0x0040E660; VectorClass<ScriptClass *> vtable 0x0079ab34 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class ScriptClass;

template class VectorClass<ScriptClass *>;
