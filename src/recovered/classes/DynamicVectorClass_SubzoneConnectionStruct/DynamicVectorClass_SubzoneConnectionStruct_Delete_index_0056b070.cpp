// DynamicVectorClass<SubzoneConnectionStruct>::Delete(int) (0x0056B070).
// Layout and behaviour: shared/vector_class.hpp, element shared/map_elements.hpp. The Map unit's
// out-of-line copy (a subzone's connection list; 0x00566DA7 and two more call it after ID).
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"
#include "shared/map_elements.hpp"

template class DynamicVectorClass<SubzoneConnectionStruct>;
