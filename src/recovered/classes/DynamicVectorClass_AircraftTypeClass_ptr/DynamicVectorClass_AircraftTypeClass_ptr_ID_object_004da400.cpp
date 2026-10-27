// DynamicVectorClass<AircraftTypeClass *>::ID_object (0x004DA400; DynamicVectorClass<AircraftTypeClass *> vtable 0x007a27a4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class AircraftTypeClass;

template class DynamicVectorClass<AircraftTypeClass *>;
