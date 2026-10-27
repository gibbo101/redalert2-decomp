// VectorClass<OwnerTalkClass::ConnectionListStruct *>::operator equal (0x0063FF70; VectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a900c slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class VectorClass<OwnerTalkClass::ConnectionListStruct *>;
