// DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>::Add (0x0056CD60).
// Layout and behaviour: shared/vector_class.hpp, element shared/map_elements.hpp. The Map
// unit's copy (0x00564E38 and 0x00564ED2 add a subzone connection to a hash bucket).
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/map_elements.hpp"

template class DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct> >;
