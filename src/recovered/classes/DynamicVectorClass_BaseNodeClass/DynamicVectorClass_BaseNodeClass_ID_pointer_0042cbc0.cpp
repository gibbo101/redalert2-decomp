// DynamicVectorClass<BaseNodeClass>::ID_pointer (0x0042CBC0; DynamicVectorClass<BaseNodeClass> vtable 0x0079c5c0 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// BaseNodeClass is a size-only stand-in (16 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class BaseNodeClass {
public:
    int unknown[4];
};

template class DynamicVectorClass<BaseNodeClass>;
