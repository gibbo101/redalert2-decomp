// DynamicVectorClass<HouseClass::BuildChoiceClass *>::ID_object (0x004F7BB0; DynamicVectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2cf4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class DynamicVectorClass<HouseClass::BuildChoiceClass *>;
