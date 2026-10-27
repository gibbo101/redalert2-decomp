// VectorClass<TRect<int>>::Fetch (0x0058DDE0; VectorClass<TRect<int>> vtable 0x007a5eb0 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
// TRect<int> is a size-only stand-in (16 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

template <class A0>
struct TRect {
    int unknown[4];
};

template class VectorClass<TRect<int> >;
