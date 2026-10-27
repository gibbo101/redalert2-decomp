// VectorClass<WinsockInterfaceClass::WinsockBufferType *>::Resize (0x0076BBA0; VectorClass<WinsockInterfaceClass::WinsockBufferType *> vtable 0x007afafc slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"

class WinsockInterfaceClass {
public:
    class WinsockBufferType;
};

template class VectorClass<WinsockInterfaceClass::WinsockBufferType *>;
