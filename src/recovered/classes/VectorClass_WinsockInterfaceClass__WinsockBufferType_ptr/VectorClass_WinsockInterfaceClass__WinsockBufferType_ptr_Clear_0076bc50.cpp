// VectorClass<WinsockInterfaceClass::WinsockBufferType *>::Clear (0x0076BC50; VectorClass<WinsockInterfaceClass::WinsockBufferType *> vtable 0x007afafc slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class WinsockInterfaceClass {
public:
    class WinsockBufferType;
};

template class VectorClass<WinsockInterfaceClass::WinsockBufferType *>;
