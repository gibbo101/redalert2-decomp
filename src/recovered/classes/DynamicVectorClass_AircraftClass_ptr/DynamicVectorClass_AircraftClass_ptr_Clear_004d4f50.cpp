// DynamicVectorClass<AircraftClass *>::Clear (0x004D4F50; DynamicVectorClass<AircraftClass *> vtable 0x007a23a4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class AircraftClass;

template class DynamicVectorClass<AircraftClass *>;
