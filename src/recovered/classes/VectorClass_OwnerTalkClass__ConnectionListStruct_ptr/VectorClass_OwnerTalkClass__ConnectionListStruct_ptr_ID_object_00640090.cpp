// VectorClass<OwnerTalkClass::ConnectionListStruct *>::ID_object (0x00640090; VectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a900c slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class VectorClass<OwnerTalkClass::ConnectionListStruct *>;
