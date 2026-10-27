// VectorClass<HouseClass::BuildChoiceClass *>::Fetch (0x004F6D90; VectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2d14 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class VectorClass<HouseClass::BuildChoiceClass *>;
