// bool DynamicVectorClass<AbstractClass *>::Delete(AbstractClass * const &object) (0x0069ED40).
// Instantiated from shared/vector_class.hpp; called by the SuperClass code (0x0069D333 and three more) for the AbstractClass list at 0x00AC0BF8 (vtable 0x007A177C).
// Expands Delete(int); this unit's own copy of Delete(int) is the one at 0x00454B20.
// @ref ?Delete@?$DynamicVectorClass@PAVAbstractClass@@@@QAE_NH@Z=00454b20
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"

class AbstractClass;

template class DynamicVectorClass<AbstractClass *>;
