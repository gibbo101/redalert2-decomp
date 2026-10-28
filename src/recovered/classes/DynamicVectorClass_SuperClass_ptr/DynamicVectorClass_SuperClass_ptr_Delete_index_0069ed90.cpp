// bool DynamicVectorClass<SuperClass *>::Delete(int index) (0x0069ED90).
// Instantiated from shared/vector_class.hpp; called at 0x0069D25E for the SuperClass list (0x00A35DB8).
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"

class SuperClass;

template class DynamicVectorClass<SuperClass *>;
