// DynamicVectorClass<AircraftTypeClass *>::ID_pointer (0x004FA690; TypeList<AircraftTypeClass *> vtable 0x007a30b8 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class AircraftTypeClass;

template class DynamicVectorClass<AircraftTypeClass *>;
