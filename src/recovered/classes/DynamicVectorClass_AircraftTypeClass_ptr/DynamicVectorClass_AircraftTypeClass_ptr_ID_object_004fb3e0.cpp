// DynamicVectorClass<AircraftTypeClass *>::ID_object (0x004FB3E0; TypeList<AircraftTypeClass *> vtable 0x007a30b8 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class AircraftTypeClass;

template class DynamicVectorClass<AircraftTypeClass *>;
