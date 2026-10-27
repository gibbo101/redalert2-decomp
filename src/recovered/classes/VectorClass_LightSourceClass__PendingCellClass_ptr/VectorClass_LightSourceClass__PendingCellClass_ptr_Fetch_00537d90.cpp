// VectorClass<LightSourceClass::PendingCellClass *>::Fetch (0x00537D90; VectorClass<LightSourceClass::PendingCellClass *> vtable 0x007a5514 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class LightSourceClass {
public:
    class PendingCellClass;
};

template class VectorClass<LightSourceClass::PendingCellClass *>;
