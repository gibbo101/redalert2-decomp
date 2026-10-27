// DynamicVectorClass<AircraftTypeClass *>::Resize (0x004FB2E0; TypeList<AircraftTypeClass *> vtable 0x007a30b8 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class AircraftTypeClass;

template class DynamicVectorClass<AircraftTypeClass *>;
