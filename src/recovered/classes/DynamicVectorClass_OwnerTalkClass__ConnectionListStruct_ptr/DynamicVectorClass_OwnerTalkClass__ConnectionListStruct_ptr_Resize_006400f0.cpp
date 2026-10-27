// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>::Resize (0x006400F0; DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a8fec slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>;
