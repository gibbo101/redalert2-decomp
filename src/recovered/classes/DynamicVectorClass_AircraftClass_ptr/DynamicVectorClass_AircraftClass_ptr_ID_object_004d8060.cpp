// DynamicVectorClass<AircraftClass *>::ID_object (0x004D8060; DynamicVectorClass<AircraftClass *> vtable 0x007a23a4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class AircraftClass;

template class DynamicVectorClass<AircraftClass *>;
