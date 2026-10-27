// VectorClass<OwnerTalkClass::ConnectionListStruct *>::ID_pointer (0x006400D0; VectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a900c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class VectorClass<OwnerTalkClass::ConnectionListStruct *>;
