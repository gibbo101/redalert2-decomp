// VectorClass<OwnerTalkClass::ConnectionListStruct *>::Fetch (0x0063FF60; VectorClass<OwnerTalkClass::ConnectionListStruct *> vtable 0x007a900c slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class OwnerTalkClass {
public:
    class ConnectionListStruct;
};

template class VectorClass<OwnerTalkClass::ConnectionListStruct *>;
