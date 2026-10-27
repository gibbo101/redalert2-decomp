// VectorClass<BuildingClass *>::ID_pointer (0x004D5CD0; VectorClass<BuildingClass *> vtable 0x007a2384 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class BuildingClass;

template class VectorClass<BuildingClass *>;
