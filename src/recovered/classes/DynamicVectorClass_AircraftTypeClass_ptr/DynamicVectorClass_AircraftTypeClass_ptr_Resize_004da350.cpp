// DynamicVectorClass<AircraftTypeClass *>::Resize (0x004DA350; DynamicVectorClass<AircraftTypeClass *> vtable 0x007a27a4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class AircraftTypeClass;

template class DynamicVectorClass<AircraftTypeClass *>;
