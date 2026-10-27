// DynamicVectorClass<LightSourceClass::PendingCellClass *>::ID_object (0x00538230; DynamicVectorClass<LightSourceClass::PendingCellClass *> vtable 0x007a54f4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class LightSourceClass {
public:
    class PendingCellClass;
};

template class DynamicVectorClass<LightSourceClass::PendingCellClass *>;
