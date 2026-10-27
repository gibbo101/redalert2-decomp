// VectorClass<AircraftClass *>::Clear (0x004D7F20; VectorClass<AircraftClass *> vtable 0x007a23c4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class AircraftClass;

template class VectorClass<AircraftClass *>;
