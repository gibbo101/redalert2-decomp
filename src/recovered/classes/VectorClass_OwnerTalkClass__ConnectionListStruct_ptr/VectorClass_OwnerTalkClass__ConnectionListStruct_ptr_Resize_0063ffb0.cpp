// VectorClass<OwnerTalkClass::ConnectionListStruct *>::Resize (0x0063FFB0; VectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a900c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class VectorClass<OwnerTalkClass::ConnectionListStruct *>;
