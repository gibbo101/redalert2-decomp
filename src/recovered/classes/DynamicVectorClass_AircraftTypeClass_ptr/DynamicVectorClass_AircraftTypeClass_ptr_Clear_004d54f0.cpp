// DynamicVectorClass<AircraftTypeClass *>::Clear (0x004D54F0; DynamicVectorClass<AircraftTypeClass *> vtable 0x007a27a4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class AircraftTypeClass;

template class DynamicVectorClass<AircraftTypeClass *>;
