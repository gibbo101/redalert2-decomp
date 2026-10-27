// VectorClass<AircraftClass *>::Fetch (0x004D4FA0; VectorClass<AircraftClass *> vtable 0x007a23c4 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class AircraftClass;

template class VectorClass<AircraftClass *>;
