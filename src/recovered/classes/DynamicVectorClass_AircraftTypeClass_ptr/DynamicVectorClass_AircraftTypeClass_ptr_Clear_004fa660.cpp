// DynamicVectorClass<AircraftTypeClass *>::Clear (0x004FA660; TypeList<AircraftTypeClass *> vtable 0x007a30b8 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class AircraftTypeClass;

template class DynamicVectorClass<AircraftTypeClass *>;
