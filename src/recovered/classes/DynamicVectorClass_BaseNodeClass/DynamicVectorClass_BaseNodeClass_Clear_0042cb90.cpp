// DynamicVectorClass<BaseNodeClass>::Clear (0x0042CB90; DynamicVectorClass<BaseNodeClass> vtable 0x0079c5c0 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class BaseNodeClass;

template class DynamicVectorClass<BaseNodeClass>;
