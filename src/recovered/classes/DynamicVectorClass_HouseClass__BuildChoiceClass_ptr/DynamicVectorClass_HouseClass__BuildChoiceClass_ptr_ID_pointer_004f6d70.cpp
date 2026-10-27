// DynamicVectorClass<HouseClass::BuildChoiceClass *>::ID_pointer (0x004F6D70; DynamicVectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2cf4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class DynamicVectorClass<HouseClass::BuildChoiceClass *>;
