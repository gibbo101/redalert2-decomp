// VectorClass<InfantryClass *>::operator equal (0x00454130; VectorClass<InfantryClass *> vtable 0x0079d074 slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class InfantryClass;

template class VectorClass<InfantryClass *>;
