// VectorClass<TRect<int>>::Clear (0x0058E690; VectorClass<TRect<int>> vtable 0x007a5eb0 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

template <class A0>
struct TRect;

template class VectorClass<TRect<int> >;
