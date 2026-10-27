// VectorClass<CommandClass *>::Fetch (0x0040BDB0; VectorClass<CommandClass *> vtable 0x0079a83c slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class CommandClass;

template class VectorClass<CommandClass *>;
