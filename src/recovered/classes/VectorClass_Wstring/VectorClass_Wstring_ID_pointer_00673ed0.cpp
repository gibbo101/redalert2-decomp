// VectorClass<Wstring>::ID_pointer (0x00673ED0; VectorClass<Wstring> vtable 0x007a9644 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// Wstring is a size-only stand-in (4 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct Wstring {
    int unknown[1];
};

template class VectorClass<Wstring>;
