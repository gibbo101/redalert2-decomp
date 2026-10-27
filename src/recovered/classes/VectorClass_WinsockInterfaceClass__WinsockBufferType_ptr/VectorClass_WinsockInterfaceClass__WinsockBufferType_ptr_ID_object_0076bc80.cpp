// VectorClass<WinsockInterfaceClass::WinsockBufferType *>::ID_object (0x0076BC80; VectorClass<WinsockInterfaceClass::WinsockBufferType *> vtable 0x007afafc slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class WinsockInterfaceClass {
public:
    class WinsockBufferType;
};

template class VectorClass<WinsockInterfaceClass::WinsockBufferType *>;
