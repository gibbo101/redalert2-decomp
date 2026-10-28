// bool DynamicVectorClass<IonBlastClass *>::Delete(int index) (0x00522500).
// Instantiated from shared/vector_class.hpp; called by the IonBlastClass destructor for the IonBlastClass list (0x00A51F88, vtable 0x007A45D4).
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"

class IonBlastClass;

template class DynamicVectorClass<IonBlastClass *>;
