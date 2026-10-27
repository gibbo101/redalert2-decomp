// DynamicVectorClass<AircraftTypeClass *>::ID_pointer (0x004D5520; DynamicVectorClass<AircraftTypeClass *> vtable 0x007a27a4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class AircraftTypeClass;

template class DynamicVectorClass<AircraftTypeClass *>;
