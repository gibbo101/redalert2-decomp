// DynamicVectorClass<HouseClass::BuildChoiceClass *>::Resize (0x004F7B00; DynamicVectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2cf4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class DynamicVectorClass<HouseClass::BuildChoiceClass *>;
