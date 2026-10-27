// VectorClass<OwnerTalkClass::ConnectionListStruct *>::Clear (0x00640060; VectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a900c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class VectorClass<OwnerTalkClass::ConnectionListStruct *>;
