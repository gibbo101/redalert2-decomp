// DynamicVectorClass<AircraftClass *>::ID_pointer (0x004D4F80; DynamicVectorClass<AircraftClass *> vtable 0x007a23a4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class AircraftClass;

template class DynamicVectorClass<AircraftClass *>;
