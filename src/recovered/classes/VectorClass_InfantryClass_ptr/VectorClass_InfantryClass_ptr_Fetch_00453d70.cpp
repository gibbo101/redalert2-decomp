// VectorClass<InfantryClass *>::Fetch (0x00453D70; VectorClass<InfantryClass *> vtable 0x0079d074 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class InfantryClass;

template class VectorClass<InfantryClass *>;
