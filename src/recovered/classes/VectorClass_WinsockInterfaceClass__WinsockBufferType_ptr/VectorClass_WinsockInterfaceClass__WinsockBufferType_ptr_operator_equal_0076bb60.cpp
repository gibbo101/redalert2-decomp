// VectorClass<WinsockInterfaceClass::WinsockBufferType *>::operator equal (0x0076BB60; VectorClass<WinsockInterfaceClass::WinsockBufferType *> vtable 0x007afafc slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class WinsockInterfaceClass {
public:
    class WinsockBufferType;
};

template class VectorClass<WinsockInterfaceClass::WinsockBufferType *>;
