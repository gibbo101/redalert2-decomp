// DynamicVectorClass<HouseClass *>::Delete (index; 0x004F8C20).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"

class HouseClass;

template class DynamicVectorClass<HouseClass *>;
