// DynamicVectorClass<HouseClass::BuildChoiceClass *>::Clear (0x004F6D40; DynamicVectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2cf4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class DynamicVectorClass<HouseClass::BuildChoiceClass *>;
