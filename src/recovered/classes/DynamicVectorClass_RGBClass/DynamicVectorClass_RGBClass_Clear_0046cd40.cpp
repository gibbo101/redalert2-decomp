// DynamicVectorClass<RGBClass>::Clear (0x0046CD40; TypeList<RGBClass> vtable 0x0079da74 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct RGBClass;

template class DynamicVectorClass<RGBClass>;
