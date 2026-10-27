#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"
class TechnoTypeClass;
// Original RTTI at vtable007A0F44 encodes pointers to const TechnoTypeClass.
// The base and derived lookup share semantics but have distinct original copies.
template class DynamicVectorClass<TechnoTypeClass const *>;
