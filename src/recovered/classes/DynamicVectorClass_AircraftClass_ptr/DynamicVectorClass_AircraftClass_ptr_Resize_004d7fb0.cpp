// DynamicVectorClass<AircraftClass *>::Resize (0x004D7FB0; DynamicVectorClass<AircraftClass *> vtable 0x007a23a4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class AircraftClass;

template class DynamicVectorClass<AircraftClass *>;
