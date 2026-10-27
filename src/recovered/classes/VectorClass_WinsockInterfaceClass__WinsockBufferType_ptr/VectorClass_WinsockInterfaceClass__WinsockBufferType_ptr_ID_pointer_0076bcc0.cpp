// VectorClass<WinsockInterfaceClass::WinsockBufferType *>::ID_pointer (0x0076BCC0; VectorClass<WinsockInterfaceClass::WinsockBufferType *> vtable 0x007afafc slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class WinsockInterfaceClass {
public:
    class WinsockBufferType;
};

template class VectorClass<WinsockInterfaceClass::WinsockBufferType *>;
