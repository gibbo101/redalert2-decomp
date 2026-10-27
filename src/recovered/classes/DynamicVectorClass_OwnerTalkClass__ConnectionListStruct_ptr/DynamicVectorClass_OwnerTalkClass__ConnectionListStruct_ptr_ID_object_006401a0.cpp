// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>::ID_object (0x006401A0; DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a8fec slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>;
