// VectorClass<WinsockInterfaceClass::WinsockBufferType *>::Fetch (0x0076BB50; VectorClass<WinsockInterfaceClass::WinsockBufferType *> vtable 0x007afafc slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class WinsockInterfaceClass {
public:
    class WinsockBufferType;
};

template class VectorClass<WinsockInterfaceClass::WinsockBufferType *>;
