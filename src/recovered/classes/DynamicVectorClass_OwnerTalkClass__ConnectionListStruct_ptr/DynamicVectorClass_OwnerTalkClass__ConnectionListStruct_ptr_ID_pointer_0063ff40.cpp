// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>::ID_pointer (0x0063FF40; DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a8fec slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>;
