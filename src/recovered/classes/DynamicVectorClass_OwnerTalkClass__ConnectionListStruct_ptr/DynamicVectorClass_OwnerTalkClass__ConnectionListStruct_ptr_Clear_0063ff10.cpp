// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>::Clear (0x0063FF10; DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a8fec slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>;
